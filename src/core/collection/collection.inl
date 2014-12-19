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

#ifndef _COLLECTION_INL_
#define _COLLECTION_INL_

inline std::vector<Glib::ustring>& Collection::getManufacturers(void)
{
	return m_manufactureres;
}

inline std::vector<Glib::ustring>& Collection::getGenres(void)
{
	return m_genres;
}

inline int Collection::platformCount(void)
{
	return m_size;
}

#endif // _COLLECTION_INL_
