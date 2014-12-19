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

#ifndef _PLATFORM_INL_
#define _PLATFORM_INL_

inline Glib::ustring& Platform::getDir(void)
{
	return m_dir;
}

inline Platform* Platform::getNext(void)
{
	return m_next;
}

inline void Platform::setNext(Platform* next)
{
	m_next = next;
}

inline Platform* Platform::getPrev(void)
{
	return m_prev;
}

inline void Platform::setPrev(Platform* prev)
{
	m_prev = prev;
}

inline Glib::ustring Platform::getName(void)
{
	return m_name;
}

inline Glib::ustring Platform::getTitle(void)
{
	return m_title;
}

inline void Platform::setTitle(const Glib::ustring& title)
{
	m_title = title;
}

inline Glib::ustring Platform::getManufacturer(void)
{
	return m_manufacturer;
}

inline void Platform::setManufacturer(const Glib::ustring& manufacturer)
{
	m_manufacturer = manufacturer;
}

inline Glib::ustring Platform::getYear(void)
{
	return m_year;
}

inline void Platform::setYear(const Glib::ustring& year)
{
	m_year = year;
}

inline Glib::ustring Platform::getRomsDir(void)
{
	return m_roms_dir;
}

inline Glib::ustring Platform::getRomsExtension(void)
{
	return m_roms_extension;
}

inline void Platform::setRomExtension(const Glib::ustring& extension)
{
	m_roms_extension = extension;
}

inline Glib::ustring Platform::getEmulatorBinary(void)
{
	return m_emu_binary;
}

inline void Platform::setEmulatorBinary(const Glib::ustring& binary)
{
	m_emu_binary = binary;
}

inline Glib::ustring Platform::getEmulatorParams(void)
{
	return m_emu_params;
}

inline void Platform::setEmulatorParams(const Glib::ustring& params)
{
	m_emu_params = params;
}

inline Glib::ustring Platform::getPreCommand(void)
{
	return m_pre_command;
}

inline void Platform::setPreCommand(const Glib::ustring& command)
{
	m_pre_command = command;
}

inline Glib::ustring Platform::getPostCommand(void)
{
	return m_post_command;
}

inline void Platform::setPostCommand(const Glib::ustring& command)
{
	m_post_command = command;
}

inline Glib::ustring Platform::getRunDir(void)
{
	return m_run_dir;
}

inline void Platform::setRunDir(const Glib::ustring& dir)
{
	m_run_dir = dir;
}

inline std::vector<Glib::ustring>& Platform::getGamelists(void)
{
	return m_lists_names;
}

inline Gamelist* Platform::gamelistGet(void)
{
	return m_master;
}

inline int Platform::gamelistCount(void)
{
	return m_lists_names.size();
}

inline Glib::ustring Platform::itemName(void)
{
	return m_name;
}

inline Glib::ustring Platform::itemTitle(void)
{
	return m_title;
}

inline Glib::ustring Platform::itemResourcesDir(void)
{
	return m_resources_dir;
}

#endif // _PLATFORM_INL_
