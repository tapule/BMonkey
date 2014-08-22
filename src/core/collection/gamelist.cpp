/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * bmonkey
 * Copyright (C) 2014 Juan Ángel Moreno Fernández
 *
 * bmonkey is free software.
 *
 * You can redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * bmonkey is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bmonkey.  If not, see <http://www.gnu.org/licenses/>
 */

#include "gamelist.hpp"
#include <glibmm.h>
#include <cassert>
#include <vector>
#include "../../utils/xml_reader.hpp"
#include "../../utils/xml_writer.hpp"

namespace bmonkey{

Gamelist::Gamelist(const Glib::ustring& name, Glib::ustring& resources_dir, Gamelist* master):
	m_resources_dir(resources_dir),
	m_master(master),
	m_name(name),
	m_is_master(master == NULL),
	m_is_filtered(false),
	m_size(0),
	m_size_filtered(0),
	m_first(NULL),
	m_last(NULL),
	m_first_filtered(NULL),
	m_last_filtered(NULL)
{
	assert(!m_resources_dir.empty());

	if (m_is_master)
	{
		// Construimos el fichero de la lista master
		m_file = Glib::build_filename(m_resources_dir, BMONKEY_GAMES_FILE);
	}
	else
	{
		// Construimos el fichero de la lista
		m_file = Glib::build_filename(m_resources_dir, PLATFORM_GAMELISTS_DIR);
		m_file = Glib::build_filename(m_file, m_name + ".xml");
	}
}

Gamelist::~Gamelist()
{
	clean();
}

bool Gamelist::loadGames(void)
{
	XmlReader xml;
	XmlNode root;
	XmlNode::iterator game_iter, field_iter;
	Game* game = NULL;
	Game game_tmp(m_resources_dir);
	Glib::ustring name;

	LOG_INFO("Gamelist: Loading games from file \"" << m_file << "\"...");
	if (xml.open(m_file))
	{
		root = xml.getRootElement();		// <gamelist>
		if (root.getName() == "gamelist")
		{
			// Limpiamos los juegos almacenados
			clean();
			// Recorremos los juegos
			for (game_iter = root.begin(); game_iter != root.end(); ++game_iter)
			{
				if (game_iter->getName() != "game")
				{
					continue;
				}
				if (isMaster())
				{
					game = new Game(m_resources_dir);
					game_iter->getAttribute("rating", game->rating);
					game_iter->getAttribute("timesplayed", game->times_played);
					game_iter->getAttribute("favorite", game->favorite);
					for (field_iter = game_iter->begin(); field_iter != game_iter->end(); ++field_iter)
					{
						name = field_iter->getName();
						if (name == "title")
						{
							field_iter->getContent(game->title);
						}
						else if (name == "cloneof")
						{
							field_iter->getContent(game->cloneof);
						}
						else if (name == "crc")
						{
							field_iter->getContent(game->crc);
						}
						else if (name == "manufacturer")
						{
							field_iter->getContent(game->manufacturer);
						}
						else if (name == "year")
						{
							field_iter->getContent(game->year);
						}
						else if (name == "genre")
						{
							field_iter->getContent(game->genre);
						}
						else if (name == "players")
						{
							field_iter->getAttribute("simultaneous", game->simultaneous);
							field_iter->getContent(game->players);
						}
					}
				}
				else
				{
					game = &game_tmp;
				}
				game_iter->getAttribute("name", game->name);
				if (!gameAdd(game) && isMaster())
				{
					delete game;
				}
			}
			xml.close();
			return true;
		}
		LOG_INFO("Gamelist: Root node \"gamelist\" not found in \""<< m_file << "\"");
		xml.close();
		return false;
	}
	LOG_ERROR("Gamelist: Can't open gamelist file \""<< m_file << "\" for reading");
	return false;
}

bool Gamelist::saveGames(void)
{
	XmlWriter xml;
	GameNode node_tmp;
	GameNode* node = &node_tmp;
	Game* game;

	LOG_INFO("Gamelist: Saving gamelist file \"" << m_file << "\"...");

	if (!xml.open(m_file))
	{
		LOG_ERROR("Gamelist: Can't open gamelist file \""<< m_file << "\" for writing");
		return false;
	}

	xml.startElement("gamelist");
	if (m_size)
	{
		// Iteramos sobre los nodos en vez de sobre el mapa ya que es aquí donde
		// realmente están ordenados.
		// Ponemos un nodo temporal como último
		m_last->setNext(&node_tmp);
		node = m_first;
		while (node != &node_tmp)
		{
			game = node->getGame();
			xml.startElement("game");
			xml.writeAttribute("name", game->name);
			if (isMaster())
			{
				xml.writeAttribute("rating", game->rating);
				xml.writeAttribute("timesplayed", game->times_played);
				xml.writeAttribute("favorite", game->favorite);
				xml.startElement("title");
					xml.writeContent(game->title);
				xml.endElement();
				xml.startElement("cloneof");
					xml.writeContent(game->cloneof);
				xml.endElement();
				xml.startElement("crc");
					xml.writeContent(game->crc);
				xml.endElement();
				xml.startElement("manufacturer");
					xml.writeContent(game->manufacturer);
				xml.endElement();
				xml.startElement("year");
					xml.writeContent(game->year);
				xml.endElement();
				xml.startElement("genre");
					xml.writeContent(game->genre);
				xml.endElement();
				xml.startElement("players");
					xml.writeAttribute("simultaneous", game->simultaneous);
					xml.writeContent(game->players);
				xml.endElement();
			}
			xml.endElement();
			node = node->getNext();
		}
	}
	xml.endElement();
	xml.close();
	return true;
}

void Gamelist::filter(std::vector<Filter* >& filters)
{
	int i;
	Glib::ustring search;
	GameNode node_tmp;
	GameNode* node = &node_tmp;

	m_is_filtered = true;

	// Si no hay elementos no se filtra
	if (m_size == 0)
	{
		return;
	}

	// Comprobamos si hay un filtro de búsqueda e inicializamos regex
	if (filters[Filter::SEARCH] != NULL)
	{
		search = filters[Filter::SEARCH]->value_txt;
		// Escapamos caracteres especiales en la cadena y añadimos marcador de inicio
		search = "^" + Glib::Regex::escape_string(search);
		// Restauramos las apariciones de * para permitir la sustitución de 0 o más caracteres
		i = search.find("\\*");
		while (i > -1)
		{
			search = search.replace(i, 2, ".*");
			i = search.find("\\*", i + 1);
		}
		// Restauramos las apariciones de ? para permitir la sustitución de 0 o 1 caracter
		i = search.find("\\?");
		while (i > -1)
		{
			search = search.replace(i, 2, ".?");
			i = search.find("\\?", i + 1);
		}
		// Creamos la expresión regular para el filtrado por título
		m_regex = Glib::Regex::create(search, Glib::REGEX_CASELESS|Glib::REGEX_OPTIMIZE);
	}

	// Creamos un nodo anterior al primero para poder hacer bucles más simples
	node->setNext(m_first);
	do
	{
		node = node->getNext();
		if (applyFilters(node, filters))
		{
			if (m_size_filtered == 0)
			{
				node->setPrevFiltered(node);
				node->setNextFiltered(node);
				m_first_filtered = node;
				m_last_filtered = node;
			}
			else
			{
				node->setPrevFiltered(m_last_filtered);
				node->setNextFiltered(m_last_filtered->getNextFiltered());
				m_last_filtered->setNextFiltered(node);
				m_first_filtered->setPrevFiltered(node);
				m_last_filtered = node;
			}
			++m_size_filtered;
		}
	} while (node != m_last);
}

void Gamelist::unfilter(void)
{
	m_is_filtered = false;
	m_size_filtered = 0;
	m_first_filtered = NULL;
	m_last_filtered = NULL;
}

bool Gamelist::gameAdd(Game* game)
{
	Game* master_game = game;
	GameNode* node = NULL;

	assert(game);
	assert(!game->name.empty());

	// Forzamos el name en lowercase
	game->name = game->name.lowercase();

	// Comprobamos si el juego existe antes de insertar
	if (gameGet(game->name))
	{
		return false;
	}
	// Buscamos el juego original en la master para enlazarlo, si no existe, descartamos
	if (!isMaster())
	{
		master_game = m_master->gameGet(game->name);
		if (!master_game)
		{
			return false;
		}
	}

	// Agregamos a la lista de nodos
	node = new GameNode();
	node->setGame(master_game);
	if (m_size == 0)
	{
		node->setPrev(node);
		node->setNext(node);
		m_first = node;
		m_last = node;
	}
	else
	{
		node->setPrev(m_last);
		node->setNext(m_last->getNext());
		m_last->setNext(node);
		m_first->setPrev(node);
		m_last = node;
	}

	// Agregamos al mapa
	m_games_map[master_game->name] = node;
	++m_size;

	return true;
}

Game* Gamelist::gameGet(Item* item)
{
	GameNode* node = NULL;

	assert(item);

	node = static_cast<GameNode* >(item);

	return node->getGame();
}

Game* Gamelist::gameGet(const Glib::ustring& name)
{
	GameNode* node;

	assert(!name.empty());

	// Buscamos el nodo
	node = nodeGet(name);
	if (node)
	{
		return node->getGame();
	}
	return NULL;
}

bool Gamelist::gameDelete(const Glib::ustring& name)
{
	GameNode* node = NULL;
	std::unordered_map<std::string, GameNode*>::iterator iter;
	std::vector<Glib::ustring> gamelists;
	std::vector<Glib::ustring>::iterator list_iter;

	assert(!name.empty());

	// Lo buscamos en el mapa
	iter = m_games_map.find(name.lowercase());
	if (iter != m_games_map.end())
	{
		node = iter->second;
	}
	if (node)
	{
		// Lo quitamos de la lista
		if (m_size == 1)
		{
			m_first = NULL;
			m_last = NULL;
			m_first_filtered = NULL;
			m_last_filtered = NULL;
			m_size = 0;
			m_size_filtered = 0;
		}
		else
		{
			node->getNext()->setPrev(node->getPrev());
			node->getPrev()->setNext(node->getNext());
			if (m_last == node)
			{
				m_last = node->getPrev();
			}
			if (m_first == node)
			{
				m_first = node->getNext();
			}
			--m_size;

			// En teoría si la lista está filtrada, solamente recibiremos para
			// eliminar elementos filtrados, por lo que no es necesario comprobar
			// cada puntero al eliminar.
			if (isFiltered())
			{
				node->getNextFiltered()->setPrevFiltered(node->getPrevFiltered());
				node->getPrevFiltered()->setNextFiltered(node->getNextFiltered());
				if (m_last_filtered == node)
				{
					m_last_filtered = node->getPrevFiltered();
				}
				if (m_first_filtered == node)
				{
					m_first_filtered = node->getNextFiltered();
				}
				--m_size_filtered;
			}
		}

		// El iterado ya lo tenemos, lo quitamos del mapa
		m_games_map.erase(iter);

		// Si la lista es master, borramos el juego real
		if (isMaster())
		{
			delete node->getGame();
		}
		delete node;
		return true;
	}
	else
	{
		return false;
	}
}

Item* Gamelist::itemGet(const Glib::ustring& name)
{
	return nodeGet(name);
}

Item* Gamelist::itemFirst(void)
{
	if (isFiltered())
	{
		return m_first_filtered;
	}
	else
	{
		return m_first;
	}
}

Item* Gamelist::itemLast(void)
{
	if (isFiltered())
	{
		return m_last_filtered;
	}
	else
	{
		return m_last;
	}
}

Item* Gamelist::itemNext(Item* item)
{
	GameNode* node = NULL;

	assert(item);

	node = static_cast<GameNode* >(item);
	if (isFiltered())
	{
		return node->getNextFiltered();
	}
	else
	{
		return node->getNext();
	}
}

Item* Gamelist::itemPrev(Item* item)
{
	GameNode* node = NULL;

	assert(item);

	node = static_cast<GameNode* >(item);
	if (isFiltered())
	{
		return node->getPrevFiltered();
	}
	else
	{
		return node->getPrev();
	}
}

Item* Gamelist::itemForward(Item* item, const int count)
{
	GameNode* node = NULL;
	int i;

	assert(item);

	node = static_cast<GameNode* >(item);
	if (isFiltered())
	{
		for (i = 0; i < count; ++i)
		{
			node = node->getNextFiltered();
		}
	}
	else
	{
		for (i = 0; i < count; ++i)
		{
			node = node->getNext();
		}
	}
	// CHECKME: Devolver nulo si se llega al mismo nodo???, así se podría evitar saltos del selector que llevan al mismo nodo
	return node;
}

Item* Gamelist::itemBackward(Item* item, const int count)
{
	GameNode* node = NULL;
	int i;

	assert(item);

	node = static_cast<GameNode* >(item);
	if (isFiltered())
	{
		for (i = 0; i < count; ++i)
		{
			node = node->getPrevFiltered();
		}
	}
	else
	{
		for (i = 0; i < count; ++i)
		{
			node = node->getPrev();
		}
	}
	// CHECKME: Devolver nulo si se llega al mismo nodo???, así se podría evitar saltos del selector que llevan al mismo nodo
	return node;
}

Item* Gamelist::itemLetterForward(Item* item)
{
	GameNode* node = NULL;
	GameNode* node_pos = NULL;
	Glib::ustring title;

	assert(item);

	node = static_cast<GameNode* >(item);
	title = node->itemTitle().substr(0,1).lowercase();
	if (isFiltered())
	{
		node_pos = node->getNextFiltered();
		while ((node_pos != node) && (title.compare(node_pos->itemTitle().substr(0,1).lowercase()) == 0))
		{
			node_pos = node_pos->getNextFiltered();
		}
	}
	else
	{
		node_pos = node->getNext();
		while ((node_pos != node) && (title.compare(node_pos->itemTitle().substr(0,1).lowercase()) == 0))
		{
			node_pos = node_pos->getNext();
		}
	}
	// CHECKME: Devolver nulo si node = node_pos???, así se podría evitar saltos del selector que llevan al mismo nodo
	return node_pos;
}

Item* Gamelist::itemLetterBackward(Item* item)
{
	GameNode* node = NULL;
	GameNode* node_pos = NULL;
	Glib::ustring title;

	assert(item);

	node = static_cast<GameNode* >(item);
	title = node->itemTitle().substr(0,1).lowercase();
	if (isFiltered())
	{
		node_pos = node->getPrevFiltered();
		while ((node_pos != node) && (title.compare(node_pos->itemTitle().substr(0,1).lowercase()) == 0))
		{
			node_pos = node_pos->getPrevFiltered();
		}
	}
	else
	{
		node_pos = node->getPrev();
		while ((node_pos != node) && (title.compare(node_pos->itemTitle().substr(0,1).lowercase()) == 0))
		{
			node_pos = node_pos->getPrev();
		}
	}
	// CHECKME: Devolver nulo si node = node_pos???, así se podría evitar saltos del selector que llevan al mismo nodo
	return node_pos;
}

bool Gamelist::applyFilters(GameNode* node, std::vector<Filter* >& filters)
{
	int i, type;
	Game* game;

	assert(node);

	game = node->getGame();

	for (i = 0; i < Filter::COUNT; ++i)
	{
		if (filters[i] != NULL)
		{
			switch (i)
			{
			case Filter::SEARCH:
				if (!m_regex->match(game->title))
				{
					return false;
				}
				break;
			case Filter::FAVORITE:
				if (game->favorite != filters[i]->value)
				{
					return false;
				}
				break;
			case Filter::TYPE:
				// 0 = Original, 1 = clon
				type = game->cloneof.empty() ? 0 : 1;
				if (type != filters[i]->value)
				{
					return false;
				}
				break;
			case Filter::MANUFACTURER:
				if (game->manufacturer != filters[i]->value_txt)
				{
					return false;
				}
				break;
			case Filter::YEAR:
				if (game->year != filters[i]->value_txt)
				{
					return false;
				}
				break;
			case Filter::GENRE:
				if (game->genre != filters[i]->value_txt)
				{
					return false;
				}
				break;
			case Filter::PLAYERS:
				if (game->players != filters[i]->value)
				{
					return false;
				}
				break;
			case Filter::SIMULTANEOUS:
				if (game->simultaneous != filters[i]->value)
				{
					return false;
				}
				break;
			case Filter::RATING:
				if (game->rating != filters[i]->value)
				{
					return false;
				}
				break;
			case Filter::LETTER:
				if (game->title.substr(0,1).lowercase().compare(filters[i]->value_txt.substr(0,1).lowercase()) != 0)
				{
					return false;
				}
				break;
			case Filter::TIMES_PLAYED:
				// 0 = 0 partidas, 1 = 1 partida, 2 = más de 1
				if ((filters[i]->value == 0 and game->times_played != 0) ||	(filters[i]->value == 1 and game->times_played != 1) ||	(filters[i]->value == 2 and game->times_played < 2))
				{
					return false;
				}
				break;
			}
		}
	}
	return true;
}

GameNode* Gamelist::nodeGet(const Glib::ustring& name)
{
	std::unordered_map<std::string, GameNode*>::iterator iter;

	assert(!name.empty());

	// Buscamos el nodo
	iter = m_games_map.find(name.lowercase());
	if (iter != m_games_map.end())
	{
		return (iter->second);
	}
	return NULL;
}

void Gamelist::clean(void)
{
	GameNode node_tmp;
	GameNode* node = NULL;
	GameNode* node_pos = NULL;

	if (m_size)
	{
		// Ponemos un nodo temporal como último para controlar el final
		m_last->setNext(&node_tmp);
		node = m_first;
		while (node != &node_tmp)
		{
			node_pos = node;
			node = node->getNext();
			if (isMaster())
			{
				delete (node_pos->getGame());
			}
			delete node_pos;
		}
		m_games_map.clear();
		m_is_filtered = false;
		m_size = 0;
		m_size_filtered = 0;
		m_first = NULL;
		m_last = NULL;
		m_first_filtered = NULL;
		m_last_filtered = NULL;
	}
}

} // namespace bmonkey
