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

#ifndef _TOKENIZER_INL_
#define _TOKENIZER_INL_

inline void Tokenizer::setDelimiters(const Glib::ustring& delimiters)
{
	m_delimiters = delimiters;
}

inline void Tokenizer::setStringDetection(const bool detect)
{
	m_detect_strings = detect;
}

inline Glib::ustring::value_type Tokenizer::lastDelimiter(void)
{
	return m_last_delimiter;
}

inline Glib::ustring Tokenizer::lastDelimiterString(void)
{
	return m_last_delimiter_string;
}

inline void Tokenizer::reset(void)
{
	m_buff_pos = m_buff.begin();
	m_token.clear();
	m_last_delimiter = '\0';
}

inline bool Tokenizer::isDelimiter(void)
{
	return(m_delimiters.find(*m_buff_pos) != std::string::npos);
}

#endif // _TOKENIZER_INL_
