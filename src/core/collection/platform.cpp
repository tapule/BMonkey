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

#include "platform.hpp"
#include <glibmm.h>
#include <glibmm/fileutils.h>
#include <glibmm/ustring.h>
#include <cassert>
#include "../../utils/xml_reader.hpp"
#include "../../utils/xml_writer.hpp"

namespace bmonkey{

Platform::Platform(const Glib::ustring& name, const Glib::ustring& library_dir):
	m_library_dir(library_dir),
	m_next(NULL),
	m_prev(NULL),
	m_name(name),
	m_master(NULL)
{
	assert(!name.empty());
	assert(!library_dir.empty());

	// Construimos el directorio base de la plataforma, y el de sus recursos
	m_dir = Glib::build_filename(library_dir, name);
	m_resources_dir = Glib::build_filename(library_dir, USER_COLLECTION_DIR);
	// Directorio de roms por defecto
	m_roms_dir = Glib::build_filename(m_dir, PLATFORM_ROMS_DIR);

	// Creamos la lista master
	m_master = new Gamelist("", m_dir, NULL);
}

Platform::~Platform(void)
{
	clean();
}

void Platform::setRomsDir(const Glib::ustring& dir)
{
	if (dir.empty())
	{
		m_roms_dir = Glib::build_filename(m_dir, PLATFORM_ROMS_DIR);
	}
	else
	{
		m_roms_dir = dir;
	}
}

bool Platform::loadConfig(void)
{
	Glib::ustring file;
	XmlReader xml;
	XmlNode root;
	XmlNode::iterator field_iter;
	Glib::ustring name;

	file = Glib::build_filename(m_dir, BMONKEY_PLATFORM_FILE);

	LOG_INFO("Platform: Loading config from file \"" << file << "\"...");
	if (xml.open(file))
	{
		root = xml.getRootElement();		// <platform>
		if (root.getName() == "platform")
		{
			// Recorremos los campos
			for (field_iter = root.begin(); field_iter != root.end(); ++field_iter)
			{
				name = field_iter->getName();
				if (name == "title")
				{
					field_iter->getContent(m_title);
				}
				else if (name == "manufacturer")
				{
					field_iter->getContent(m_manufacturer);
				}
				else if (name == "year")
				{
					field_iter->getContent(m_year);
				}
				else if (name == "romsdir")
				{
					field_iter->getContent(m_roms_dir);
				}
				else if (name == "romsextension")
				{
					field_iter->getContent(m_roms_extension);
				}
				else if (name == "emubinary")
				{
					field_iter->getContent(m_emu_binary);
				}
				else if (name == "emuparams")
				{
					field_iter->getContent(m_emu_params);
				}
				else if (name == "precommand")
				{
					field_iter->getContent(m_pre_command);
				}
				else if (name == "postcommand")
				{
					field_iter->getContent(m_post_command);
				}
				else if (name == "rundir")
				{
					field_iter->getContent(m_run_dir);
				}
			}
			xml.close();
			return true;
		}
		LOG_INFO("Platform: Root node \"platform\" not found in \""<< file << "\"");
		xml.close();
		return false;
	}
	LOG_ERROR("Platform: Can't open config file \""<< file << "\" for reading");
	return false;
}

bool Platform::loadGames(void)
{
	return m_master->loadGames();
}

bool Platform::loadGamelists(void)
{
	Glib::Dir::iterator iter;
	Glib::ustring gamelists_dir;
	Glib::ustring name, extension, file;
	Gamelist* gamelist;

	gamelists_dir = Glib::build_filename(m_dir, PLATFORM_GAMELISTS_DIR);

	try
	{
		// Abrimos el directorio y vamos obteniendo los ficheros
		Glib::Dir dir(gamelists_dir);
		for (iter = dir.begin(); iter != dir.end(); ++iter)
		{
			// Comprobamos que sea un fichero regular
			file = Glib::build_filename(gamelists_dir, (*iter));
			if (Glib::file_test(file.c_str(), Glib::FILE_TEST_IS_REGULAR))
			{
				name = (*iter).substr(0, (*iter).size() - 4);
				extension = (*iter).substr((*iter).size() - 4, 4);
				// Comprobamos que sea un xml
				if (extension.lowercase() == ".xml")
				{
					gamelist = new Gamelist(name, m_dir, m_master);
					m_lists_map[name.lowercase()] = gamelist;
					m_lists_names.push_back(name);
					gamelist->loadGames();
				}
			}
		}
		return true;
	}
	catch (Glib::Error& e)
	{
		LOG_ERROR("Platform: Reading gamelists (" << e.what().c_str() << ")");
	}
	return false;
}

bool Platform::saveConfig(void)
{
	Glib::ustring file;
	XmlWriter xml;

	file = Glib::build_filename(m_dir, BMONKEY_PLATFORM_FILE);

	LOG_INFO("Platform: Saving config file \"" << file << "\"...");

	if (!xml.open(file))
	{
		LOG_ERROR("Platform: Can't open config file \""<< file << "\" for writing");
		return false;
	}

	xml.startElement("platform");
		xml.startElement("title");
			xml.writeContent(m_title);
		xml.endElement();
		xml.startElement("manufacturer");
			xml.writeContent(m_manufacturer);
		xml.endElement();
		xml.startElement("year");
			xml.writeContent(m_year);
		xml.endElement();
		xml.startElement("romsdir");
			xml.writeContent(m_roms_dir);
		xml.endElement();
		xml.startElement("romsextension");
			xml.writeContent(m_roms_extension);
		xml.endElement();
		xml.startElement("emubinary");
			xml.writeContent(m_emu_binary);
		xml.endElement();
		xml.startElement("emuparams");
			xml.writeContent(m_emu_params);
		xml.endElement();
		xml.startElement("precommand");
			xml.writeContent(m_pre_command);
		xml.endElement();
		xml.startElement("postcommand");
			xml.writeContent(m_post_command);
		xml.endElement();
		xml.startElement("rundir");
			xml.writeContent(m_run_dir);
		xml.endElement();
	xml.endElement();
	xml.close();
	return true;
}

bool Platform::saveGames(void)
{
	return m_master->saveGames();
}

bool Platform::saveGamelists(void)
{
	std::unordered_map<std::string, Gamelist* >::iterator iter;

	for (iter = m_lists_map.begin(); iter != m_lists_map.end(); ++iter)
	{
		iter->second->saveGames();
	}
	return true;
}

bool Platform::gameDelete(const Glib::ustring& name, Gamelist* list)
{
	std::unordered_map<std::string, Gamelist* >::iterator iter;

	assert(!name.empty());
	assert(list);

	if (list->isMaster())
	{
		for (iter = m_lists_map.begin(); iter != m_lists_map.end(); ++iter)
		{
			iter->second->gameDelete(name);
		}
	}
	list->gameDelete(name);
	return true;
}

Gamelist* Platform::gamelistGet(const Glib::ustring& name)
{
	std::unordered_map<std::string, Gamelist* >::iterator iter;

	assert(!name.empty());

	// Buscamos la lista
	iter = m_lists_map.find(name.lowercase());
	if (iter != m_lists_map.end())
	{
		return (iter->second);
	}
	return NULL;
}

Gamelist* Platform::gamelistCreate(const Glib::ustring& name)
{
	Gamelist* list = NULL;

	assert(!name.empty());

	// Comprobamos si la list existe antes de crear
	if (gamelistGet(name))
	{
		return NULL;
	}

	list = new Gamelist(name, m_dir, m_master);
	m_lists_map[name.lowercase()] = list;
	m_lists_names.push_back(name);

	return list;
}

void Platform::clean(void)
{
	std::unordered_map<std::string, Gamelist* >::iterator iter;

	// Borramos las listas
	for (iter = m_lists_map.begin(); iter != m_lists_map.end(); ++iter)
	{
		delete iter->second;
	}
	delete m_master;

	m_lists_map.clear();
	m_lists_names.clear();
}

} // namespace bmonkey
