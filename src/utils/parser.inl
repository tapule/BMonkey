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

#ifndef _PARSER_INL_
#define _PARSER_INL_

inline bool Parser::initFromMemory(const char *buffer, const unsigned int size)
{
	return m_tokenizer.initFromMemory(buffer, size);
}

inline bool Parser::initFromFile(const Glib::ustring& file)
{
	return m_tokenizer.initFromFile(file);
}

inline bool Parser::initFromString(const Glib::ustring& str)
{
	return m_tokenizer.initFromString(str);
}

inline void Parser::setDelimiters(const Glib::ustring& delimiters)
{
	m_tokenizer.setDelimiters(delimiters);
}

inline void Parser::setReservedWords(const std::vector<ReservedWord>& words)
{
	m_words = words;
	std::sort(m_words.begin(), m_words.end(), Parser::compareWords);
}

inline void Parser::setStringDetection(const bool detect)
{
	m_tokenizer.setStringDetection(detect);
}

inline void Parser::setNumberDetection(const bool detect)
{
	m_detect_numbers = detect;
}

inline bool Parser::hasMoreTokens(void)
{
	return m_tokenizer.hasMoreTokens();
}

inline Glib::ustring::value_type Parser::lastDelimiter(void)
{
	return m_tokenizer.lastDelimiter();
}

inline Glib::ustring Parser::lastDelimiterString(void)
{
	return m_tokenizer.lastDelimiterString();
}

inline void Parser::reset()
{
	m_tokenizer.reset();
}

inline bool Parser::compareWords(const ReservedWord& word0, const ReservedWord& word1)
{
	return (word0.name.compare(word1.name) < 0);
}

inline int Parser::binarySearchWord(const Glib::ustring& key)
{
	int top = m_words.size() - 1;
	int bottom = 0;
	int center;
	int str_cmp;

	while (bottom <= top)
	{
		center = (top + bottom)/2;
		str_cmp = m_words[center].name.compare(key);
		if (str_cmp == 0)
		{
			return center;
		}
		else
		{
			if (str_cmp > 0)
			{
				top = center - 1;
			}
			else
			{
				bottom = center + 1;
			}
		}
	}
	return -1;
}

#endif // _PARSER_INL_
