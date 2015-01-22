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

#include "font_library.hpp"
#include <cassert>
#include <glibmm/miscutils.h>
#include <glibmm/fileutils.h>

namespace bmonkey{


FontLibrary::FontLibrary(void)
{
	LOG_INFO("FontLibrary: Loading default font...");
	if (!m_system_font.loadFromFile(Glib::build_filename(BMONKEY_FONTS_DIR, BMONKEY_DEFAULT_FONT_FILE)))
	{
		LOG_ERROR("FontLibrary: Can't open default font \""<< BMONKEY_DEFAULT_FONT_FILE << "\"");
		exit(EXIT_FAILURE);
	}
}

FontLibrary::~FontLibrary(void)
{
	clean();
}

sf::Font* FontLibrary::loadFont(const Glib::ustring& file)
{
	std::vector<Resource >::iterator iter;
	Resource resource;

	if (file.empty())
	{
		return nullptr;
	}

	// Comprobamos si ya tenemos la fuente cargada
	for (iter = m_fonts.begin(); iter != m_fonts.end(); ++iter)
	{
		if (iter->file == file)
		{
			// Incrementamos contador de referencias
			++iter->count;
			return iter->font;
		}
	}
	// No encontramos la fuente, tratamos de cargarla
	resource.file = file;
	resource.count = 1;
	resource.font = new sf::Font();
	// Cargamos la nueva fuente y la almacenamos
	if (!resource.font->loadFromFile(file))
	{
		delete resource.font;
		return nullptr;
	}
	else
	{
		m_fonts.push_back(resource);
	}
	return resource.font;
}

sf::Font* FontLibrary::getSystemFont(void)
{
	return (&m_system_font);
}

void FontLibrary::deleteFont(sf::Font* font)
{
	std::vector<Resource >::iterator iter;

	// Buscamos la fuente
	for (iter = m_fonts.begin(); iter != m_fonts.end(); ++iter)
	{
		if (iter->font == font)
		{
			// Decrementamos el contador de referencias
			--iter->count;
			// Si no hay más referencias descargamos la fuente
			if (iter->count == 0)
			{
				delete iter->font;
				m_fonts.erase(iter);
			}
		}
	}
}

void FontLibrary::clean(void)
{
	std::vector<Resource >::iterator iter;

	for (iter = m_fonts.begin(); iter != m_fonts.end(); ++iter)
	{
		delete iter->font;
	}
	m_fonts.clear();
}

} // namespace bmonkey
