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

#include "collection.hpp"
#include <glibmm.h>
#include <cassert>
#include <algorithm>
#include "../../utils/xml_reader.hpp"
#include "../../utils/xml_writer.hpp"
#include "../../utils/utils.hpp"
#include "gamelist.hpp"

namespace bmonkey{

Collection::Collection(const Glib::ustring& working_dir):
	m_working_dir(working_dir),
	m_size(0),
	m_first(NULL),
	m_last(NULL)
{
	assert(!m_working_dir.empty());
}

Collection::~Collection(void)
{
	clean();
}

bool Collection::loadConfig(void)
{
	Glib::ustring file, library_dir;
	XmlReader xml;
	XmlNode root;
	XmlNode::iterator platform_iter;
	Glib::ustring name;
	Platform* platform = NULL;

	file = Glib::build_filename(m_working_dir, BMONKEY_COLLECTION_FILE);
	library_dir = Glib::build_filename(m_working_dir, USER_LIBRARY_DIR);

	LOG_INFO("Collection: Loading config from file \"" << file << "\"...");
	if (xml.open(file))
	{
		root = xml.getRootElement();		// <collection>
		if (root.getName() == "collection")
		{
			// Recorremos las plataformas
			for (platform_iter = root.begin(); platform_iter != root.end(); ++platform_iter)
			{
				if (platform_iter->getName() != "platform")
				{
					continue;
				}
				platform_iter->getContent(name);
				platform = new Platform(name.lowercase(), library_dir);
				if (!platformAdd(platform))
				{
					delete platform;
				}
			}
			xml.close();
			return true;
		}
		LOG_INFO("Collection: Root node \"collection\" not found in \""<< file << "\"");
		xml.close();
		return false;
	}
	LOG_ERROR("Collection: Can't open config file \""<< file << "\" for reading");
	return false;
}

bool Collection::loadPlatforms(void)
{
	std::unordered_map<std::string, Platform* >::iterator iter;

	for (iter = m_platforms_map.begin(); iter != m_platforms_map.end(); ++iter)
	{
		iter->second->loadConfig();
		iter->second->loadGames();
		iter->second->loadGamelists();
	}
	// Una vez cargadas las plataformas, generamos las tablas de fabricantes y Géneros
	generateDinamicTables();

	return true;
}

bool Collection::saveConfig(void)
{
	Glib::ustring file;
	XmlWriter xml;
	Platform platform_tmp("__tmp", "__tmp");
	Platform* platform = NULL;

	file = Glib::build_filename(m_working_dir, BMONKEY_COLLECTION_FILE);

	LOG_INFO("Collection: Saving config file \"" << file << "\"...");

	if (!xml.open(file))
	{
		LOG_ERROR("Collection: Can't open config file \""<< file << "\" for writing");
		return false;
	}

	xml.startElement("collection");
	if (m_size)
	{
		// Ponemos una plataforma temporal como último elemento
		m_last->setNext(&platform_tmp);
		platform = m_first;
		while (platform != &platform_tmp)
		{
			xml.startElement("platform");
				xml.writeContent(platform->getName());
			xml.endElement();
			platform = platform->getNext();
		}
	}
	xml.endElement();
	xml.close();
	return true;
}

bool Collection::savePlatforms(void)
{
	std::unordered_map<std::string, Platform* >::iterator iter;

	for (iter = m_platforms_map.begin(); iter != m_platforms_map.end(); ++iter)
	{
		iter->second->saveGamelists();
		iter->second->saveGames();
		iter->second->saveConfig();
	}
	return true;
}

Platform* Collection::platformGet(Item* item)
{
	Platform* platform = NULL;

	assert(item);

	platform = static_cast<Platform* >(item);

	return platform;
}

Platform* Collection::platformGet(const Glib::ustring& name)
{
	std::unordered_map<std::string, Platform*>::iterator iter;

	assert(!name.empty());

	// Buscamos el nodo
	iter = m_platforms_map.find(name.lowercase());
	if (iter != m_platforms_map.end())
	{
		return (iter->second);
	}
	return NULL;
}

Platform* Collection::platformCreate(const Glib::ustring& name)
{
	Platform* platform = NULL;
	Glib::ustring library_dir, platform_dir, tmp_dir;

	assert(!name.empty());

	// Antes de crear, comprobamos si la plataforma ya existe
	platform = platformGet(name);
	if (platform)
	{
		return platform;
	}

	library_dir = Glib::build_filename(m_working_dir, USER_LIBRARY_DIR);

	// Creamos y añadimos
	platform = new Platform(name.lowercase(), library_dir);
	platform->setTitle(name);
	if (!platformAdd(platform))
	{
		delete platform;
		platform = NULL;
	}
	else
	{
		// Creamos la estructura de directorios para la plataforma
		LOG_INFO("Collection: Creating platform directory...");
		platform_dir = Glib::build_filename(library_dir, platform->getName());
		if (!utils::checkOrCreateDir(platform_dir))
		{
			LOG_ERROR("Collection: Creating platform directory \"" << platform_dir << "\"");
		}
		tmp_dir = Glib::build_filename(platform_dir, PLATFORM_ROMS_DIR);
		if (!utils::checkOrCreateDir(tmp_dir))
		{
			LOG_ERROR("Collection: Creating platform roms directory \"" << tmp_dir << "\"");
		}
		tmp_dir = Glib::build_filename(platform_dir, PLATFORM_GAMELISTS_DIR);
		if (!utils::checkOrCreateDir(tmp_dir))
		{
			LOG_ERROR("Collection: Creating platform gamelists directory \"" << tmp_dir << "\"");
		}
		tmp_dir = Glib::build_filename(platform_dir, PLATFORM_BACKGROUNDS_DIR);
		if (!utils::checkOrCreateDir(tmp_dir))
		{
			LOG_ERROR("Collection: Creating platform backgrounds directory \"" << tmp_dir << "\"");
		}
		tmp_dir = Glib::build_filename(platform_dir, PLATFORM_SNAPS_DIR);
		if (!utils::checkOrCreateDir(tmp_dir))
		{
			LOG_ERROR("Collection: Creating platform snaps directory \"" << tmp_dir << "\"");
		}
		tmp_dir = Glib::build_filename(platform_dir, PLATFORM_WHEELS_DIR);
		if (!utils::checkOrCreateDir(tmp_dir))
		{
			LOG_ERROR("Collection: Creating platform wheels directory \"" << tmp_dir << "\"");
		}
		tmp_dir = Glib::build_filename(platform_dir, PLATFORM_VIDEOS_DIR);
		if (!utils::checkOrCreateDir(tmp_dir))
		{
			LOG_ERROR("Collection: Creating platform videos directory \"" << tmp_dir << "\"");
		}
	}

	return platform;
}

Item* Collection::itemGet(const Glib::ustring& name)
{
	return platformGet(name);
}

Item* Collection::itemFirst(void)
{
	return m_first;
}

Item* Collection::itemLast(void)
{
	return m_last;
}

Item* Collection::itemNext(Item* item)
{
	Platform* platform = NULL;

	assert(item);

	platform = static_cast<Platform* >(item);
	return platform->getNext();
}

Item* Collection::itemPrev(Item* item)
{
	Platform* platform = NULL;

	assert(item);

	platform = static_cast<Platform* >(item);
	return platform->getPrev();
}

Item* Collection::itemForward(Item* item, const int count)
{
	Platform* platform = NULL;
	int i;

	assert(item);

	platform = static_cast<Platform* >(item);
	for (i = 0; i < count; ++i)
	{
		platform = platform->getNext();
	}
	// CHECKME: Devolver nulo si se llega a la misma plataforma???, así se podría evitar saltos del selector que llevan al mismo elemento
	return platform;
}

Item* Collection::itemBackward(Item* item, const int count)
{
	Platform* platform = NULL;
	int i;

	assert(item);

	platform = static_cast<Platform* >(item);
	for (i = 0; i < count; ++i)
	{
		platform = platform->getPrev();
	}

	// CHECKME: Devolver nulo si se llega a la misma plataforma???, así se podría evitar saltos del selector que llevan al mismo elemento
	return platform;
}

Item* Collection::itemLetterForward(Item* item)
{
	Platform* platform = NULL;
	Platform* platform_pos = NULL;
	Glib::ustring title;

	assert(item);

	platform = static_cast<Platform* >(item);
	title = platform->itemTitle().substr(0,1).lowercase();
	platform_pos = platform->getNext();
	while ((platform_pos != platform) && (title.compare(platform_pos->itemTitle().substr(0,1).lowercase()) == 0))
	{
		platform_pos = platform_pos->getNext();
	}

	// CHECKME: Devolver nulo si se llega a la misma plataforma???, así se podría evitar saltos del selector que llevan al mismo elemento
	return platform_pos;
}

Item* Collection::itemLetterBackward(Item* item)
{
	Platform* platform = NULL;
	Platform* platform_pos = NULL;
	Glib::ustring title;

	assert(item);

	platform = static_cast<Platform* >(item);
	title = platform->itemTitle().substr(0,1).lowercase();
	platform_pos = platform->getPrev();
	while ((platform_pos != platform) && (title.compare(platform_pos->itemTitle().substr(0,1).lowercase()) == 0))
	{
		platform_pos = platform_pos->getPrev();
	}

	// CHECKME: Devolver nulo si se llega a la misma plataforma???, así se podría evitar saltos del selector que llevan al mismo elemento
	return platform_pos;
}

bool Collection::platformAdd(Platform* platform)
{
	assert(platform);
	assert(!platform->getName().empty());

	// Como este método es privado, no es necesario pasar el nombre a minúsculas
	// sabemos que ya vendrá en este formato

	// Comprobamos si la plataforma existe antes de insertar
	if (platformGet(platform->getName()))
	{
		return false;
	}

	// Agregamos a la lista de plataformas
	if (m_size == 0)
	{
		platform->setPrev(platform);
		platform->setNext(platform);
		m_first = platform;
		m_last = platform;
	}
	else
	{
		platform->setPrev(m_last);
		platform->setNext(m_last->getNext());
		m_last->setNext(platform);
		m_first->setPrev(platform);
		m_last = platform;
	}

	// Agregamos al mapa
	m_platforms_map[platform->getName()] = platform;
	++m_size;

	return true;
}

void Collection::generateDinamicTables(void)
{
	std::unordered_map<std::string, Platform* >::iterator iter;
	std::unordered_map<std::string, std::string> manufacturers_map;
	std::unordered_map<std::string, std::string> genres_map;
	std::unordered_map<std::string, std::string>::iterator tmp_iter;
	Gamelist* list;
	Item* first = NULL;
	Item* item = NULL;
	Glib::ustring str;

	// Limpiamos los vectores antes de nada
	m_manufactureres.clear();
	m_genres.clear();

	// Construimos las tablas sin duplicados
	for (iter = m_platforms_map.begin(); iter != m_platforms_map.end(); ++iter)
	{
		list = iter->second->gamelistGet();
		if (list->gameCount())
		{
			item = list->itemFirst();
			first = item;
			do
			{
				str = list->gameGet(item)->manufacturer;
				if (!str.empty())
				{
					tmp_iter = manufacturers_map.find(str);
					if (tmp_iter == manufacturers_map.end())
					{
						manufacturers_map[str] = str;
						m_manufactureres.push_back(str);
					}
				}
				str = list->gameGet(item)->genre;
				if (!str.empty())
				{
					tmp_iter = genres_map.find(str);
					if (tmp_iter == genres_map.end())
					{
						genres_map[str] = str;
						m_genres.push_back(str);
					}
				}
				item = list->itemNext(item);
			} while (item != first);
		}
	}

	// Ordenamos las tablas
	std::sort(m_manufactureres.begin(), m_manufactureres.end());
	std::sort(m_genres.begin(), m_genres.end());

	// Limpiamos recursos
	manufacturers_map.clear();
	genres_map.clear();
}

void Collection::clean(void)
{
	Platform platform_tmp("_tmp", "_tmp");
	Platform* platform = NULL;
	Platform* platform_pos = NULL;

	if (m_size)
	{
		// Ponemos una plataforma temporal como último para controlar el final
		m_last->setNext(&platform_tmp);
		platform = m_first;
		while (platform != &platform_tmp)
		{
			platform_pos = platform;
			platform = platform->getNext();
			delete platform_pos;
		}
		m_platforms_map.clear();
		m_size = 0;
		m_first = NULL;
		m_last = NULL;
		m_manufactureres.clear();
		m_genres.clear();
	}
}

} // namespace bmonkey
