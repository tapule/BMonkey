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

#ifndef _GAMELIST_INL_
#define _GAMELIST_INL_

inline Glib::ustring Gamelist::getName(void)
{
	return m_name;
}

inline bool Gamelist::isMaster(void)
{
	return m_is_master;
}

inline void Gamelist::setMaster(const bool is_master)
{
	m_is_master = is_master;
}

inline bool Gamelist::isFiltered(void)
{
	return m_is_filtered;
}

inline int Gamelist::gameCount(void)
{
	return m_size;
}

inline int Gamelist::gameCountFiltered(void)
{
	return m_size_filtered;
}

#endif // _GAMELIST_INL_
