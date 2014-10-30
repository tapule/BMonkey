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

#include "texture_manager.hpp"
#include <cassert>

namespace bmonkey{

bool TextureManager::m_instantiated = false;

TextureManager::TextureManager(void):
	m_smooth(false)
{
	// Con este assert forzamos una instancia única de la clase
	assert(!m_instantiated);
	m_instantiated = true;
}

TextureManager::~TextureManager(void)
{
	clean();
	// Si se destruye la instancia, permitimos que se cree de nuevo
	m_instantiated = false;
}

sf::Texture* TextureManager::loadTexture(const Glib::ustring& file, const bool repeated)
{
	std::unordered_map<std::string, Resource >::iterator iter;
	Resource resource;

	if (file.empty())
	{
		return nullptr;
	}

	// Comprobamos si ya tenemos la textura cargada
	iter = m_textures.find(file);
	if (iter != m_textures.end() )
	{
		// Incrementamos contador de referencias
		++iter->second.count;
		iter->second.texture->setRepeated(repeated);
		return iter->second.texture;
	}
	else
	{
		resource.texture = new sf::Texture();
		// Cargamos la nueva textura y la almacenamos
		if (!resource.texture->loadFromFile(file))
		{
			delete resource.texture;
			return nullptr;
		}
		else
		{
			resource.count = 1;
			resource.texture->setRepeated(repeated);
			resource.texture->setSmooth(m_smooth);
			m_textures[file] = resource;
		}
		return resource.texture;
	}
}

sf::Texture* TextureManager::getTexture(const Glib::ustring& file)
{
	std::unordered_map<std::string, Resource >::iterator iter;

	if (file.empty())
	{
		return nullptr;
	}

	// Buscamos la textura
	iter = m_textures.find(file);
	if (iter != m_textures.end() )
	{
		return iter->second.texture;
	}
	else
	{
		return nullptr;
	}
}

void TextureManager::deleteTexture(const Glib::ustring& file)
{
	std::unordered_map<std::string, Resource >::iterator iter;

	if (file.empty())
	{
		return;
	}

	// Buscamos la textura
	iter = m_textures.find(file);
	if (iter != m_textures.end() )
	{
		// Decrementamos el contador de referencias
		--iter->second.count;
		// Si no hay más referencias descargamos la textura
		if (iter->second.count == 0)
		{
			delete iter->second.texture;
			m_textures.erase(iter);
		}
	}
}

void TextureManager::setSmooth(const bool smooth)
{
	std::unordered_map<std::string, Resource >::iterator iter;

	for (iter = m_textures.begin(); iter != m_textures.end(); ++iter)
	{
		iter->second.texture->setSmooth(smooth);
	}
	m_smooth = smooth;
}

void TextureManager::clean(void)
{
	std::unordered_map<std::string, Resource >::iterator iter;

	for (iter = m_textures.begin(); iter != m_textures.end(); ++iter)
	{
		delete iter->second.texture;
	}
	m_textures.clear();
}

} // namespace bmonkey
