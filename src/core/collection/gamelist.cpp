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

namespace bmonkey{

Gamelist::Gamelist(const Glib::ustring& name, Platform* platform):
	m_platform(platform),
	m_name(name),
	m_is_master(false),
	m_size(0),
	m_size_filtered(0),
	m_first(NULL),
	m_last(NULL),
	m_first_filtered(NULL),
	m_last_filtered(NULL)
{
	Glib::ustring::size_type i;

	assert(platform);

	if (m_name.empty())
	{
		m_is_master = true;
		// Construimos el fichero de la lista master
		m_file = Glib::build_filename(m_platform->getDir(), BMONKEY_GAMES_FILE);
	}
	else
	{
		// Construimos el fichero de la lista
		m_file = Glib::build_filename(m_platform->getDir(), PLATFORM_GAMELISTS_DIR);
		m_file = Glib::build_filename(m_file, m_name + ".xml");
	}
}

Gamelist::~Gamelist()
{
	clean();
}

inline Glib::ustring Gamelist::getName(void)
{
	return m_name;
}

inline bool Gamelist::isMaster(void)
{
	return m_is_master;
}

inline void Gamelist::setMaster(const bool is_master)
{
	m_is_master = is_master;
}

bool Gamelist::loadGames(void)
{
	XmlReader xml;
	XmlNode root;
	XmlNode::iterator game_iter, field_iter;
	Game* game = NULL;
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
				game = new game();
				game_iter->getAttribute("name", game->name);
				if (isMaster())
				{
					game_iter->getAttribute("type", game->type);
					game_iter->getAttribute("rating", game->rating);
					game_iter->getAttribute("timesplayed", game->times_played);
					game_iter->getAttribute("favorite", game->favorite);
					for (field_iter = game_iter->begin(); field_iter != game_iter->end(); ++field_iter)
					{
						name = field_iter->getName();
						if (name == "crc")
						{
							field_iter->getContent(game->crc);
						}
						else if (name == "title")
						{
							field_iter->getContent(game->title);
						}
						else if (name == "manufacturer")
						{
							field_iter->getContent(game->manufacturer);
						}
						else if (name == "year")
						{
							field_iter->getContent(game->year);
						}
						else if (name == "players")
						{
							field_iter->getContent(game->players);
						}
						else if (name == "simultaneous")
						{
							field_iter->getContent(game->simultaneous);
						}
					}
				}
				gameAdd(game);
				if (!isMaster())
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
		// Ponemos un nodo temporal como último
		m_last->m_next = &node_tmp;
		node = m_first;
		while (node != &node_tmp)
		{
			game = node->gameGet();
			xml.startElement("game");
			xml.writeAttribute("name", game->name);
			if (isMaster())
			{
				xml.writeAttribute("type", game->type);
				xml.writeAttribute("rating", game->rating);
				xml.writeAttribute("timesplayed", game->times_played);
				xml.writeAttribute("favorite", game->favorite);
				xml.startElement("crc");
				xml.writeContent(game->crc);
				xml.endElement();
				xml.startElement("title");
				xml.writeContent(game->title);
				xml.endElement();
				xml.startElement("manufacturer");
				xml.writeContent(game->manufacturer);
				xml.endElement();
				xml.startElement("year");
				xml.writeContent(game->year);
				xml.endElement();
				xml.startElement("players");
				xml.writeContent(game->players);
				xml.endElement();
				xml.startElement("simultaneous");
				xml.writeContent(game->simultaneous);
				xml.endElement();
			}
			xml.endElement();
			node = node->m_next;
		}
	}
	xml.endElement();
	xml.close();
	return true;
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
	// Buscamos el juego original en la master para enlazarlo
	if (!isMaster())
	{
		master_game = m_platform->gamelistGet()->gameGet(game->name);
		if (!master_game)
		{
			return false;
		}
	}

	// Agregamos a la lista de nodos
	node = new GameNode();
	node->gameSet(master_game);
	if (m_size == 0)
	{
		node->m_prev = node;
		node->m_next = node;
		m_first = node;
		m_last = node;
	}
	else
	{
		node->m_prev = m_last;
		node->m_next = m_last->m_next;
		m_last->m_next = node;
		m_first->m_prev = node;
		m_last = node;
	}

	// Agregamos al mapa
	m_games_map[master_game->name.raw()] = node;
	++m_size;

	return true;
}

Game* Gamelist::gameGet(Item* item)
{
	GameNode* node = NULL;

	assert(item);

	node = static_cast<GameNode* >(item);

	return node->gameGet();
}

Game* Gamelist::gameGet(const Glib::ustring& name)
{
	GameNode* node;

	assert(!name.empty());

	// Buscamos el nodo
	node = nodeGet(name);
	if (node)
	{
		return node->gameGet();
	}
	return NULL;
}

bool Gamelist::gameDelete(GameNode* node)
{
	std::unordered_map<std::string, GameNode*>::iterator iter;
	std::vector<Glib::ustring> gamelists;
	std::vector<Glib::ustring>::iterator list_iter;

	assert(node);
	assert(m_size);

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
		node->m_next->m_prev = node->m_prev;
		node->m_prev->m_next = node->m_next;
		if (m_last == node)
		{
			m_last = node->m_prev;
		}
		if (m_first == node)
		{
			m_first = node->m_next;
		}
		--m_size;

		// En teoría si la lista está filtrada, solamente recibiremos para
		// eliminar elementos filtrados, por lo que no es necesario comprobar
		// cada puntero al eliminar.
		if (isFiltered())
		{
			node->m_next_filtered->m_prev_filtered = node->m_prev_filtered;
			node->m_prev_filtered->m_next_filtered = node->m_next_filtered;
			if (m_last_filtered == node)
			{
				m_last_filtered = node->m_prev_filtered;
			}
			if (m_first_filtered == node)
			{
				m_first_filtered = node->m_next_filtered;
			}
			--m_size_filtered;
		}
	}

	// Lo quitamos del mapa
	iter = m_games_map.find(node->getName());
	if (iter != m_games_map.end())
	{
		m_games_map.erase(iter);
	}

	// Si la lista es master, forzamos la eliminación en el resto de listas y borramos el juego real
	if (isMaster())
	{
		gamelists = m_platform->getGamelists();
		for (list_iter = gamelists.begin(); list_iter != gamelists.end(); ++list_iter)
		{
			m_platform->gamelistGet(*list_iter)->gameDelete(node->getName());
		}
		delete node->gameGet();
	}

	delete node;

	return true;
}

bool Gamelist::gameDelete(const Glib::ustring& name)
{
	GameNode* node = NULL;

	assert(!name.empty());

	node = nodeGet(name);
	if (node)
	{
		return gameDelete(node);
	}
	else
	{
		return false;
	}
}

inline int Gamelist::gameCount(void)
{
	return m_size;
}

inline int Gamelist::gameCountFiltered(void)
{
	return m_size_filtered;
}

void Gamelist::filter(std::vector<Filter* >& filters)
{
	int i;
	Glib::ustring search;
	GameNode node_tmp;
	GameNode* node = &node_tmp;

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
	node->m_next = m_first;
	do
	{
		node = node->m_next;
		if (applyFilters(node, filters))
		{
			if (m_size_filtered == 0)
			{
				node->m_prev_filtered = node;
				node->m_next_filtered = node;
				m_first_filtered = node;
				m_last_filtered = node;
			}
			else
			{
				node->m_prev_filtered = m_last_filtered;
				node->m_next_filtered = m_last_filtered->m_next_filtered;
				m_last_filtered->m_next_filtered = node;
				m_first_filtered->m_prev_filtered = node;
				m_last_filtered = node;
			}
			++m_size_filtered;
		}
	} while (node != m_last);
}

bool Gamelist::applyFilters(GameNode* node, std::vector<Filter* >& filters)
{
	int i;
	Game* game;
	bool visible = true;

	assert(node);

	game = node->gameGet();

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
				if (game->type != filters[i]->value)
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
				if (game->title.compare(0, 1, filters[i]->value_txt) != 0)
				{
					return false;
				}
				break;
			case Filter::TIMES_PLAYED:
				if ((game->times_played < 2 && game->times_played != filters[i]->value) || (filters[i]->value == 2 && game->times_played < 2))
				{
					return false;
				}
				break;
			}
		}
	}
	return true;
}

inline bool Gamelist::isFiltered(void)
{
	return (m_size_filtered > 0);
}

void Gamelist::unfilter(void)
{
	m_size_filtered = 0;
	m_first_filtered = NULL;
	m_last_filtered = NULL;
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
		return node->m_next_filtered;
	}
	else
	{
		return node->m_next;
	}
}

Item* Gamelist::itemPrev(Item* item)
{
	GameNode* node = NULL;

	assert(item);

	node = static_cast<GameNode* >(item);
	if (isFiltered())
	{
		return node->m_prev_filtered;
	}
	else
	{
		return node->m_prev;
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
		for (i = 0; i< count; ++i)
		{
			node = node->m_next_filtered;
		}
	}
	else
	{
		for (i = 0; i< count; ++i)
		{
			node = node->m_next;
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
		for (i = 0; i< count; ++i)
		{
			node = node->m_prev_filtered;
		}
	}
	else
	{
		for (i = 0; i< count; ++i)
		{
			node = node->m_prev;
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
	title = node->getTitle().substr(0,1).lowercase();
	if (isFiltered())
	{
		node_pos = node->m_next_filtered;
		while ((node_pos != node) && (title.compare(node_pos->getTitle().substr(0,1).lowercase()) == 0))
		{
			node_pos = node_pos->m_next_filtered;
		}
	}
	else
	{
		node_pos = node->m_next;
		while ((node_pos != node) && (title.compare(node_pos->getTitle().substr(0,1).lowercase()) == 0))
		{
			node_pos = node_pos->m_next;
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
	title = node->getTitle().substr(0,1).lowercase();
	if (isFiltered())
	{
		node_pos = node->m_prev_filtered;
		while ((node_pos != node) && (title.compare(node_pos->getTitle().substr(0,1).lowercase()) == 0))
		{
			node_pos = node_pos->m_prev_filtered;
		}
	}
	else
	{
		node_pos = node->m_prev;
		while ((node_pos != node) && (title.compare(node_pos->getTitle().substr(0,1).lowercase()) == 0))
		{
			node_pos = node_pos->m_prev;
		}
	}
	// CHECKME: Devolver nulo si node = node_pos???, así se podría evitar saltos del selector que llevan al mismo nodo
	return node_pos;
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
	GameNode* node = &node_tmp;
	GameNode* node_pos = NULL;

	if (m_size)
	{
		// Ponemos un nodo temporal como último
		m_last->m_next = &node_tmp;
		node = m_first;
		while (node != &node_tmp)
		{
			node_pos = node;
			node = node->m_next;
			if (isMaster())
			{
				delete (node_pos->gameGet());
			}
			delete node_pos;
		}
		m_games_map.clear();
		m_size = 0;
		m_size_filtered = 0;
		m_first = NULL;
		m_last = NULL;
		m_first_filtered = NULL;
		m_last_filtered = NULL;
	}
}

} // namespace bmonkey
