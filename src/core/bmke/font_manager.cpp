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

#include "font_manager.hpp"
#include <cassert>
#include <glibmm/miscutils.h>
#include <glibmm/fileutils.h>

namespace bmonkey{


FontManager* FontManager::m_font_manager = nullptr;

FontManager::FontManager(void):
	m_system_fonts(COUNT)
{
	LOG_INFO("FontManager: Loading default fonts...");
	if (!m_system_fonts[0].loadFromFile(Glib::build_filename(BMONKEY_FONTS_DIR, BMONKEY_DEFAULT_FONT_FILE)))
	{
		LOG_ERROR("FontManager: Can't open default font \""<< BMONKEY_DEFAULT_FONT_FILE << "\"");
		exit(EXIT_FAILURE);
	}
}

FontManager::~FontManager(void)
{
	clear();
}

FontManager* FontManager::getInstance(void)
{
	if (!m_font_manager)
	{
		m_font_manager = new FontManager();
	}
	return m_font_manager;
}

sf::Font* FontManager::loadFont(const Glib::ustring& file)
{
	std::unordered_map<std::string, Resource >::iterator iter;
	Resource resource;

	if (file.empty())
	{
		return nullptr;
	}

	// Comprobamos si ya tenemos la fuente cargada
	iter = m_fonts.find(file);
	if (iter != m_fonts.end() )
	{
		// Incrementamos contador de referencias
		++iter->second.count;
		return iter->second.font;
	}
	else
	{
		resource.font = new sf::Font();
		// Cargamos la nueva fuente y la almacenamos
		if (!resource.font->loadFromFile(file))
		{
			delete resource.font;
			return nullptr;
		}
		else
		{
			resource.count = 1;
			m_fonts[file] = resource;
		}
		return resource.font;
	}
}

sf::Font* FontManager::getFont(const Glib::ustring& file)
{
	std::unordered_map<std::string, Resource >::iterator iter;

	if (file.empty())
	{
		return nullptr;
	}

	// Buscamos la fuente
	iter = m_fonts.find(file);
	if (iter != m_fonts.end() )
	{
		return iter->second.font;
	}
	else
	{
		return nullptr;
	}
}

sf::Font* FontManager::getSystemFont(const SystemFonts id)
{
	assert(id < COUNT);

	return (&m_system_fonts[id]);
}

void FontManager::deleteFont(const Glib::ustring& file)
{
	std::unordered_map<std::string, Resource >::iterator iter;

	if (file.empty())
	{
		return;
	}

	// Buscamos la fuente
	iter = m_fonts.find(file);
	if (iter != m_fonts.end() )
	{
		// Decrementamos el contador de referencias
		--iter->second.count;
		// Si no hay más referencias descargamos la fuente
		if (iter->second.count == 0)
		{
			delete iter->second.font;
			m_fonts.erase(iter);
		}
	}
}

void FontManager::clear(void)
{
	std::unordered_map<std::string, Resource >::iterator iter;

	for (iter = m_fonts.begin(); iter != m_fonts.end(); ++iter)
	{
		delete iter->second.font;
	}
	m_fonts.clear();
}

} // namespace bmonkey
