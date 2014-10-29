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

#include "graphics.hpp"
#include <cassert>
#include <glibmm/miscutils.h>

namespace bmonkey{

bool Graphics::m_instantiated = false;

Graphics::Graphics(Config* config):
	m_init(false),
	m_config(config),
	m_rotation(NONE)
{
	assert(config);

	// Con este assert forzamos una instancia única de la clase
	assert(!m_instantiated);
	m_instantiated = true;
}

Graphics::~Graphics(void)
{
	// Si se destruye la instancia, permitimos que se cree de nuevo
	m_instantiated = false;
}

void Graphics::init(void)
{
	Glib::ustring working_dir;
	bool fullscreen = false;
	unsigned int width = 800;
	unsigned int height = 600;
	unsigned int bpp = 32;
	Glib::ustring rotation_txt = "none";
	Rotation rotation = NONE;
	sf::ContextSettings ctx_settings;
	unsigned int antialiasing_level = 0;
	bool vsync = false;
	unsigned int fps_limit = 0;
	float joystick_threshold = 75.f;
	//float mouse_threshold;
	unsigned int style;

	LOG_INFO("Graphics: Initializing...");
	m_init = true;

	// Montamos el directorio para las capturas de pantalla
	m_config->getKey(BMONKEY_CFG_GLOBAL, "current_working_dir", working_dir);
	m_screenshot_dir = Glib::build_filename(working_dir, USER_SCREENSHOT_DIR);

	// Comprobamos las variables de configuración y fijamos valores por defecto
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "fullscreen", fullscreen))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "fullscreen", fullscreen);
	}
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "width", width))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "width", width);
		m_config->setKey(BMONKEY_CFG_SCREEN, "heigth", height);
	}
	else
	{
		if (!m_config->getKey(BMONKEY_CFG_SCREEN, "heigth", height))
		{
			m_config->setKey(BMONKEY_CFG_SCREEN, "heigth", height);
		}
	}
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "bpp", bpp))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "bpp", bpp);
	}
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "rotation", rotation_txt))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "rotation", rotation_txt);
	}
	else
	{
		rotation_txt = rotation_txt.lowercase();
		if (rotation_txt == "left")
		{
			rotation = LEFT;
		}
		else if (rotation_txt == "right")
		{
			rotation = RIGHT;
		}
		else if (rotation_txt == "inverted")
		{
			rotation = INVERTED;
		}
	}

	LOG_INFO("Graphics: Mode " << width << "x" << height << "x" << bpp << ", Fullscreen " << fullscreen << ", Rotation " << rotation_txt);

	if (!m_config->getKey(BMONKEY_CFG_CORE, "antialiasing_level", antialiasing_level))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "antialiasing_level", antialiasing_level);
	}
	if (!m_config->getKey(BMONKEY_CFG_CORE, "vertical_sync", vsync))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "vertical_sync", vsync);
	}
	if (!m_config->getKey(BMONKEY_CFG_CORE, "framerate_limit", fps_limit))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "framerate_limit", fps_limit);
	}
	if (!m_config->getKey(BMONKEY_CFG_CORE, "joystick_threshold", joystick_threshold))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "joystick_threshold", joystick_threshold);
	}

	if (fullscreen)
	{
		style = sf::Style::Fullscreen;
	}
	else
	{
		style = sf::Style::Titlebar | sf::Style::Close;
	}

	ctx_settings.antialiasingLevel = antialiasing_level;
	m_window.create(sf::VideoMode(width, height, bpp), "BMonkey 0.1", style, ctx_settings);
	m_window.setVerticalSyncEnabled(vsync);
	// Si vsync está habilitado, el limite fps puede dar problemas
	m_window.setFramerateLimit(fps_limit);
	rotate(rotation);

	if (joystick_threshold != 0)
	{
		m_window.setJoystickThreshold(joystick_threshold);
	}
}

void Graphics::rotate(const Rotation rotation)
{
	unsigned int width;
	unsigned int height;
	sf::View view;
	std::string rotation_txt;

	assert(m_init);

	// Asumimos que previamente se etableción una resolución adecuada
	m_config->getKey(BMONKEY_CFG_SCREEN, "width", width);
	m_config->getKey(BMONKEY_CFG_SCREEN, "heigth", height);

	view = m_window.getDefaultView();
	switch(rotation)
	{
	case RIGHT:
		view.setRotation(90.f);
		view.setCenter(height/2.f, width/2.f);
		rotation_txt = "right";
		break;
	case INVERTED:
		view.setRotation(180.f);
		view.setCenter(width/2.f, height/2.f);
		rotation_txt = "inverted";
		break;
	case LEFT:
		view.setRotation(-90.f);
		view.setCenter(height/2.f, width/2.f);
		rotation_txt = "left";
		break;
	default:
		view.setRotation(0.f);
		view.setCenter(width/2.f, height/2.f);
		rotation_txt = "none";
		break;
	}
	m_window.setView(view);
	// Guardamos nueva configuración de rotación
	m_rotation = rotation;
	m_config->setKey(BMONKEY_CFG_SCREEN, "rotation", rotation_txt);
}

void Graphics::switchRotation(void)
{
	int rotation;

	assert(m_init);

	rotation = m_rotation;
	if (rotation == LEFT)
	{
		rotation = NONE;
	}
	else
	{
		++rotation;
	}
	rotate(static_cast<Rotation>(rotation));
}

void Graphics::capture(void)
{
	Glib::ustring screenshot_file;
	int id = 0;

	assert(m_init);

	do
	{
		screenshot_file = Glib::build_filename(m_screenshot_dir, "screenshot_" + utils::toStr(id) + ".png");
		++id;
	} while (Glib::file_test(screenshot_file, Glib::FILE_TEST_EXISTS));

	if(!m_window.capture().saveToFile(screenshot_file))
	{
		LOG_ERROR("Graphics: Can't create screenshot \"" << screenshot_file << "\"");
	}
	else
	{
		LOG_INFO("Graphics: Screenshot taken to \"" << screenshot_file << "\"");
	}
}

sf::RenderWindow* Graphics::getRenderWindow(void)
{
	return &m_window;
}

} // namespace bmonkey
