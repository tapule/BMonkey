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

#include "parser.hpp"
#include <fstream>
#include <cstdlib>
#include <string>

Parser::Parser(void):
	m_detect_numbers(true)
{
	// Por defecto detección de cadenas y números activada
	m_tokenizer.setStringDetection(true);
}

Parser::~Parser()
{
	m_words.clear();
}

Token Parser::nextToken(void)
{
	Token token;

	// Inicialmente marcamos como token no válido
	token.type = TK_NOTK;
	token.value = 0;

	if (m_tokenizer.hasMoreTokens())
	{
		// De momento marcamos como cadena y obtenemos esta del tokenizador
		token.type = TK_STR;
		token.string = m_tokenizer.nextToken();
		// Comprobamos si se trata de un número
		if (m_detect_numbers)
		{
			checkNum(token);
		}
		checkReservedWords(token);
	}
	else
	{
		// Si no quedan tokens, devolvemos el token fin de fichero
		token.type = TK_EOF;
	}

	return token;
}

bool Parser::checkReservedWords(Token& token)
{
	int pos;

	pos = binarySearchWord(token.string);
	if (pos != -1)
	{
		token.type = m_words[pos].type;
		token.string = m_words[pos].name;
		return true;
	}
	return false;
}

bool Parser::checkNum(Token& token)
{
	Glib::ustring::const_iterator iter;

	if (token.string.empty())
	{
		return false;
	}

	iter = token.string.begin();
	while (iter != token.string.end() && std::isdigit(*iter))
	{
		++iter;
	}

	if (iter == token.string.end())
	{
		token.type = TK_NUM;
		token.value = atoi(token.string.c_str());
		return true;
	}

	return false;
}
