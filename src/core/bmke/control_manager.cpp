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

#include "control_manager.hpp"
#include <glibmm.h>
#include <glibmm/fileutils.h>
#include <glibmm/ustring.h>
#include <cassert>
#include <cmath>
#include "../../utils/xml_reader.hpp"
#include "../../utils/xml_writer.hpp"
#include "../../utils/utils.hpp"

namespace bmonkey{

const unsigned char ControlManager::MAX_CONTROL_SETS = 2;

const std::vector<std::string> ControlManager::m_sfml_key_str =
{
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"Num0",
	"Num1",
	"Num2",
	"Num3",
	"Num4",
	"Num5",
	"Num6",
	"Num7",
	"Num8",
	"Num9",
	"Escape",
	"LControl",
	"LShift",
	"LAlt",
	"LSystem",
	"RControl",
	"RShift",
	"RAlt",
	"RSystem",
	"Menu",
	"LBracket",
	"RBracket",
	"SemiColon",
	"Comma",
	"Period",
	"Quote",
	"Slash",
	"BackSlash",
	"Tilde",
	"Equal",
	"Dash",
	"Space",
	"Return",
	"BackSpace",
	"Tab",
	"PageUp",
	"PageDown",
	"End",
	"Home",
	"Insert",
	"Delete",
	"Add",
	"Subtract",
	"Multiply",
	"Divide",
	"Left",
	"Right",
	"Up",
	"Down",
	"Numpad0",
	"Numpad1",
	"Numpad2",
	"Numpad3",
	"Numpad4",
	"Numpad5",
	"Numpad6",
	"Numpad7",
	"Numpad8",
	"Numpad9",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"Pause"
};

ControlManager::ControlManager(sf::Window& window):
	m_window(window),
	m_mouse_pos(sf::Mouse::getPosition()),
	m_ignore_alt_key(false),
	m_alt_keys(MAX_CONTROL_SETS, ""),
	m_alt_keys_status(MAX_CONTROL_SETS, false),
	m_control_sets(MAX_CONTROL_SETS, std::vector<std::string>(OTHER)),
	m_events_status(OTHER, false)
{
}

ControlManager::~ControlManager(void)
{
}

bool ControlManager::load(const Glib::ustring& file)
{
	XmlReader xml;
	XmlNode root;
	XmlNode::iterator set_iter, event_iter;
	int id;
	unsigned char set;
	Event event;
	Glib::ustring command;

	assert(!file.empty());
	m_file = file;

	LOG_INFO("ControlManager: Loading config from file \"" << m_file << "\"...");
	if (xml.open(m_file))
	{
		// Si se pudo abrir, guardamos el path del fichero
		root = xml.getRootElement();		// <keymap>
		if (root.getName() == "keymap")
		{
			// Recorremos los contols sets
			for (set_iter = root.begin(); set_iter != root.end(); ++set_iter)
			{
				if (set_iter->getName() != "controlset")
				{
					continue;
				}
				// Comprobamos que se trata de un set valido
				set_iter->getAttribute("id", id);
				if (id < 0 || id >= MAX_CONTROL_SETS)
				{
					continue;
				}
				set = static_cast<unsigned char>(id);
				// Leemos los mapeos
				for (event_iter = set_iter->begin(); event_iter != set_iter->end(); ++event_iter)
				{
					command.clear();
					if (event_iter->getName() == "altkey")
					{
						event_iter->getContent(command);
						registerAltKey(set, command);
					}
					else if (event_iter->getName() == "event")
					{
						event_iter->getAttribute("id", id);
						if (id >= 0 && id < OTHER)
						{
							event = static_cast<Event>(id);
							event_iter->getContent(command);
							registerEvent(event, set, command);
						}
					}
				}
			}
			xml.close();
			return true;
		}
		LOG_INFO("ControlManager: Root node \"keymap\" not found in \""<< m_file << "\"");
		xml.close();
		return false;
	}
	LOG_ERROR("ControlManager: Can't open keymap file \""<< m_file << "\" for reading");
	return false;
}

bool ControlManager::save(const Glib::ustring& file)
{
	XmlWriter xml;
	unsigned char set;
	int event;

	assert(!file.empty());

	LOG_INFO("ControlManager: Saving keymap file \"" << m_file << "\"...");

	if (!xml.open(file))
	{
		LOG_ERROR("ControlManager: Can't open keymap file \""<< m_file << "\" for writing");
		return false;
	}

	xml.startElement("keymap");
	for (set = 0; set < MAX_CONTROL_SETS; ++set)
	{
		xml.startElement("controlset");
			xml.writeAttribute("id", static_cast<int>(set));
			xml.startElement("altkey");
				xml.writeContent(getAltKey(set));
			xml.endElement();
			// Obtenemos el mapeo del set
			for (event = 0; event < OTHER; ++event)
			{
				xml.startElement("event");
					xml.writeAttribute("id", event);
					xml.writeContent((m_control_sets[set])[event]);
				xml.endElement();
			}
		xml.endElement();
	}
	xml.endElement();
	xml.close();
	return true;
}

bool ControlManager::poolEvent(Event& event)
{
	unsigned char set;
	sf::Event sfml_event;
	std::string command;
	std::vector<std::string>::iterator iter;
	int i;
	bool ret = false;

	while (m_window.pollEvent(sfml_event))
	{
		// Antes de nada comprobamos el evento de cierre
		if (sfml_event.type == sf::Event::Closed)
		{
			event = EXIT;
			return true;
		}
		// Si se trata de un evento que no tiene sentido para el fe, lo ignoramos
		if (sfml_event.type == sf::Event::Resized || sfml_event.type == sf::Event::LostFocus || sfml_event.type == sf::Event::GainedFocus || sfml_event.type == sf::Event::TextEntered)
		{
			continue;
		}
		// Obtenemos la representación textual del evento
		command = sfmlEventToStr(sfml_event);

		for (set = 0; set < MAX_CONTROL_SETS; ++set)
		{
			// Si se ignora la alt key, forzamos su desactivación
			if (m_ignore_alt_key)
			{
				m_alt_keys_status[set] = false;
			}
			else
			{
				// Comprobamos si es la alt key del set
				if (!command.empty() && command == m_alt_keys[set])
				{
					if (sfml_event.type == sf::Event::KeyPressed ||
						sfml_event.type == sf::Event::MouseButtonPressed ||
						sfml_event.type == sf::Event::JoystickButtonPressed)
					{
						m_alt_keys_status[set] = true;
					}
					else if (sfml_event.type == sf::Event::KeyReleased ||
						sfml_event.type == sf::Event::MouseButtonReleased ||
						sfml_event.type == sf::Event::JoystickButtonReleased)
					{
						m_alt_keys_status[set] = false;
					}
					// Si es la alt key, pasamos al siguiente evento
					break;
				}
			}
			// Si no es la alt key y es un evento release, pasamos al siguiente set
			if (sfml_event.type == sf::Event::KeyReleased ||
				sfml_event.type == sf::Event::MouseButtonReleased ||
				sfml_event.type == sf::Event::JoystickButtonReleased)
			{
				continue;
			}
			// Almacenamos el último control pulsado
			m_last_command = (m_alt_keys_status[set] == true ? "Shift + " : "") + command;

			// Buscamos el posible evento
			for (i = 0; i < OTHER; ++i)
			{
				if (m_events_status[i] && m_last_command == (m_control_sets[set])[i] )
				{
					event = static_cast<Event>(i);
					return true;
				}
			}
			// Si no hay coincidencia marcamos que hay evento pero que no es conocido
			if (i == OTHER)
			{
				event = OTHER;
				ret = true;
			}
		}
	}
	return ret;
}

void ControlManager::disableAllEvent(void)
{
	std::vector<bool>::iterator iter;

	for (iter = m_events_status.begin(); iter != m_events_status.end(); ++ iter)
	{
		*iter = false;
	}
}

void ControlManager::registerEvent(const Event& event, const unsigned char set, const std::string& command)
{
	assert(event < OTHER);
	assert(set < MAX_CONTROL_SETS);

	// Si no hay comando, no hacemos nada
	if (command.empty())
	{
		return;
	}
	// Agregamos el evento
	(m_control_sets[set])[event] = command;
}

void ControlManager::registerDefaultControls(void)
{
	// Registro de las teclas por defecto para el set 0
	registerAltKey(0, "Key " + m_sfml_key_str[sf::Keyboard::LAlt]);
	registerEvent(SELECT, 0, "Key " + m_sfml_key_str[sf::Keyboard::Return]);
	registerEvent(BACK, 0, "Key " + m_sfml_key_str[sf::Keyboard::BackSpace]);
	registerEvent(PLATFORM_PREVIOUS, 0, "Key " + m_sfml_key_str[sf::Keyboard::Left]);
	registerEvent(PLATFORM_NEXT, 0, "Key " + m_sfml_key_str[sf::Keyboard::Right]);
	registerEvent(GAME_PREVIOUS, 0, "Key " + m_sfml_key_str[sf::Keyboard::Up]);
	registerEvent(GAME_NEXT, 0, "Key " + m_sfml_key_str[sf::Keyboard::Down]);
	registerEvent(GAME_LETTER_PREVIOUS, 0, "Key " + m_sfml_key_str[sf::Keyboard::Left]);
	registerEvent(GAME_LETTER_NEXT, 0, "Key " + m_sfml_key_str[sf::Keyboard::Right]);
	registerEvent(GAME_JUMP_BACKWARD, 0, "Shift + Key " + m_sfml_key_str[sf::Keyboard::Left]);
	registerEvent(GAME_JUMP_FORWARD, 0, "Shift + Key " + m_sfml_key_str[sf::Keyboard::Right]);
	registerEvent(MENU_UP, 0, "Key " + m_sfml_key_str[sf::Keyboard::Up]);
	registerEvent(MENU_DOWN, 0, "Key " + m_sfml_key_str[sf::Keyboard::Down]);
	registerEvent(MENU_LEFT, 0, "Key " + m_sfml_key_str[sf::Keyboard::Left]);
	registerEvent(MENU_RIGHT, 0, "Key " + m_sfml_key_str[sf::Keyboard::Right]);
	registerEvent(EXIT_MENU, 0, "Key " + m_sfml_key_str[sf::Keyboard::Escape]);
	registerEvent(GAMELIST_MENU, 0, "Key " + m_sfml_key_str[sf::Keyboard::L]);
	registerEvent(VOLUME_MENU, 0, "Key " + m_sfml_key_str[sf::Keyboard::V]);
	registerEvent(FILTERS_MENU, 0, "Key " + m_sfml_key_str[sf::Keyboard::F]);
	registerEvent(GAME_MENU, 0, "Key " + m_sfml_key_str[sf::Keyboard::G]);
	registerEvent(CONTROLS_MENU, 0, "Key " + m_sfml_key_str[sf::Keyboard::C]);
	registerEvent(SWITCH_ROTATION, 0, "Key " + m_sfml_key_str[sf::Keyboard::R]);
}

std::string ControlManager::sfmlEventToStr(const sf::Event& event)
{
	std::string command;
	int offset_x, offset_y;

	switch(event.type)
	{
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
		// Sfml devuelve -1 para indicar una tecla desconocida
		if (event.key.code == sf::Keyboard::Unknown)
		{
			command = "Key Unknown";
		}
		else
		{
			command = "Key " + m_sfml_key_str[event.key.code];
		}
		break;
	case sf::Event::MouseWheelMoved:
		command = "Mouse Wh_";
		command += (event.mouseWheel.delta > 0 ? "up": "down");
		break;
	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		command = "Mouse Bt_" + utils::toStr(event.mouseButton.button);
		break;
	case sf::Event::MouseMoved:
		command = "Mouse Ax_";
		// Obtenemos los desplazamientos absolutos en cada eje
		offset_x = std::abs(event.mouseMove.x - m_mouse_pos.x);
		offset_y = std::abs(event.mouseMove.y - m_mouse_pos.y);
		// Damos prioridad a la x en caso de que coincidan los desplazamientos
		if (offset_x >= offset_y)
		{
			// Marcamos el eje X como eje 0
			command += "0";
			if (event.mouseMove.x > m_mouse_pos.x)
			{
				command += " Plus";
			}
			else
			{
				command += " Minus";
			}
		}
		else
		{
			// Marcamos el eje Y como eje 1
			command += "1";
			if (event.mouseMove.y > m_mouse_pos.y)
			{
				command += " Plus";
			}
			else
			{
				command += " Minus";
			}
		}
		m_mouse_pos.x = event.mouseMove.x;
		m_mouse_pos.y = event.mouseMove.y;
		break;
	case sf::Event::JoystickButtonPressed:
	case sf::Event::JoystickButtonReleased:
		command = "Joy_" + utils::toStr(event.joystickButton.joystickId) + " Bt_" + utils::toStr(event.joystickButton.button);
		break;
	// CHECKME: Este está sin testear
	case sf::Event::JoystickMoved:
		command = "Joy_" + utils::toStr(event.joystickMove.joystickId) + " Ax_" + utils::toStr(event.joystickMove.axis) + (event.joystickMove.position > 0 ? " Plus": " Minus");
		break;
	default:
		break;
	}
	return command;
}

} // namespace bmonkey
