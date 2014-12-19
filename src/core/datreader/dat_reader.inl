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

#ifndef _DAT_READER_INL_
#define _DAT_READER_INL_

inline bool DatReader::load(const char* buffer, const unsigned int size)
{
	return false;
}

inline bool DatReader::read(std::map<Glib::ustring, DatSet>& set_collection)
{
	return false;
}

inline bool DatReader::read(std::vector<DatSet>& set_collection)
{
	return false;
}

inline bool DatReader::isLoaded(void)
{
	return m_loaded;
}

inline Glib::ustring DatReader::getType(void)
{
	return "";
}

#endif // _DAT_PARSER_INL_
