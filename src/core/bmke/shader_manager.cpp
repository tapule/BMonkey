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

#include "shader_manager.hpp"
#include <cassert>

namespace bmonkey{

ShaderManager* ShaderManager::m_shader_manager = nullptr;

// Utilizamos un vector estático ya que usaremos pocos shaders y serán pequeños
const std::vector<std::vector<std::string> > ShaderManager::m_shaders_src =
{
	{
		// Vertex shader
	   "void main()" \
		"{" \
		"    ..." \
		"}"
		,
		// Fragment shader
	   "void main()" \
		"{" \
		"    ..." \
		"}"
	}
};

ShaderManager::ShaderManager(void):
	m_shaders(COUNT, nullptr)
{
}

ShaderManager::~ShaderManager(void)
{
	clear();
}

ShaderManager* ShaderManager::getInstance(void)
{
	if (!m_shader_manager)
	{
		m_shader_manager = new ShaderManager();
	}
	return m_shader_manager;
}

bool ShaderManager::isAvailable(void)
{
	return sf::Shader::isAvailable();
}

bool ShaderManager::loadShader(const Type type)
{
	sf::Shader* shader;
	bool ret;

	assert(type < COUNT);

	// El shader ya se cargó
	if (m_shaders[type])
	{
		return true;
	}

	if (isAvailable())
	{
		shader = new sf::Shader();
		// Cargamos dependiendo de si tenemos vertex o fragment shader
		if (!(m_shaders_src[type][0].empty()) && m_shaders_src[type][1].empty())
		{
			ret = shader->loadFromMemory(ShaderManager::m_shaders_src[type][0], sf::Shader::Vertex);
		}
		else if (m_shaders_src[type][0].empty() && !m_shaders_src[type][1].empty())
		{
			ret = shader->loadFromMemory(m_shaders_src[type][1], sf::Shader::Fragment);
		}
		else
		{
			ret = shader->loadFromMemory(m_shaders_src[type][0], m_shaders_src[type][1]);
		}

		if (!ret)
		{
			delete shader;
			return false;
		}
		m_shaders[type] = shader;
		return true;
	}
	else
	{
		return false;
	}
}

sf::Shader* ShaderManager::getShader(const Type type)
{
	assert(type < COUNT);

	if (!isAvailable())
	{
		return nullptr;
	}

	// Si no tenemos el shader, lo cargamos
	if (!m_shaders[type])
	{
		loadShader(type);
	}

	return m_shaders[type];
}

void ShaderManager::deleteShader(const Type type)
{
	assert(type < COUNT);

	delete m_shaders[type];
	m_shaders[type] = nullptr;
}

void ShaderManager::clear(void)
{
	std::vector<sf::Shader* >::iterator iter;

	if (isAvailable())
	{
		for (iter = m_shaders.begin(); iter != m_shaders.end(); ++iter)
		{
			delete (*iter);
			*iter = nullptr;
		}
	}
}

} // namespace bmonkey
