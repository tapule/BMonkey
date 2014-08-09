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
#include "../../utils/xml_reader.hpp"

namespace bmonkey{

Gamelist::Gamelist(Collection* collection, const Glib::ustring& file):
	m_collection(collection),
	m_file(file),
	m_is_master(false)
{
	Glib::ustring::size_type i;

	if (!file.empty())
	{
		m_name = Glib::path_get_basename(file);
		// Eliminamos la extensión
		i = m_name.rfind('.');
		if (i != Glib::ustring::npos)
		{
			m_name.erase(i);
		}
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

inline void Gamelist::setName(const Glib::ustring& name)
{
	m_name = name;
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
	Gamelist* master = NULL;
	Game* game = NULL;
	Glib::ustring name;

	if (m_file.empty())
	{
		return false;
	}

	// Si no es una lista master, obtenemos su master de la colección
	if (!isMaster() && m_collection != NULL)
	{
		//master = m_collection->gamelistGetMaster();
	}

	LOG_INFO("Gamelist: Loading games from file \"" << m_file << "\"...");
	if (xml.open(m_file))
	{
		root = xml.getRootElement();		// <gamelist>
		if (root.getName() == "gamelist")
		{
			// Limpiamos los almacenes internos
			clean();
			// Recorremos los juegos
			for (game_iter = root.begin(); game_iter != root.end(); ++game_iter)
			{
				if (game_iter->getName() != "game")
				{
					continue;
				}
				// Si el juego ya existe en la lista, lo ignoramos
				game_iter->getAttribute("name", name);
				if (gameFind(name) != -1)
				{
					continue;
				}

				if (isMaster())
				{


				}
				else
				{

				}
				// Obtenemos los valores de las claves
				for (key_iter = group_iter->begin(); key_iter != group_iter->end(); ++key_iter)
				{
					key_iter->getAttribute("name", key_name);
					key_iter->getAttribute("value", key_value);
					key_map[key_name] = key_value;
				}
				group_iter->getAttribute("name", group_name);
				// Creamos el grupo con una copia del mapa de claves creado
				m_groups[group_name] = key_map;
				key_map.clear();
			}
			return true;
		}
		LOG_INFO("Config: Root node \"" << m_root<< "\" not found in \""<< file << "\"");
		return false;
	}
	LOG_ERROR("Config: Can't open config file \""<< file << "\" for reading");
	return false;
}



void Gamelist::clean(void)
{
	std::vector<Game* >::iterator iter;

	// Si es una lista master, eliminamos sus juegos
	if (isMaster())
	{
		for (iter = m_games.begin(); iter != m_games.end(); ++iter)
		{
			delete (*iter);
		}
	}
	m_games.clear();
	m_games_map.clear();
}

} // namespace bmonkey
