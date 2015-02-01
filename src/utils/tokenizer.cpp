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

#include "tokenizer.hpp"
#include <fstream>

Tokenizer::Tokenizer(void):
	m_delimiters(DEFAULT_DELIMITERS),
	m_last_delimiter('\0'),
	m_detect_strings(true)
{
	m_buff_pos = m_buff.begin();
}

Tokenizer::~Tokenizer()
{
}

bool Tokenizer::initFromMemory(const char *buffer, const unsigned int size)
{
	// Usamos ustring.assign(InputIterator begin, InputIterator end) en vez de
	// ustring.assign(const char*, size_type) porque esta segunda versión espera
	// la longitud del buffer en "caracteres" no en bytes y por lo tanto puede
	// producir errores/excepciones
	m_buff.assign(buffer, buffer + size);
	m_buff_pos = m_buff.begin();
	m_token.clear();
	m_last_delimiter = '\0';

	return true;
}

bool Tokenizer::initFromFile(const Glib::ustring& file)
{
	std::ifstream file_stream;
	unsigned int size;
	char* buff = nullptr;

	assert(!file.empty());

	file_stream.open(file.data());
	if (!file_stream.good())
	{
		file_stream.close();
		return false;
	}
	// Obtenemos el tamaño del fichero para redimensionar la cadena
	file_stream.seekg (0, std::ios::end);
	size = file_stream.tellg();
	file_stream.seekg (0, std::ios::beg);

	// Reservamos la memoria necesaria
	buff = new char[size];
	if (!buff)
	{
		file_stream.close();
		return false;
	}

	// Cargamos el contenido completo del fichero en el buffer
	file_stream.read(buff, size);
	file_stream.close();
	// Inicializamos el string interno
	initFromMemory(buff, size);

	delete[] buff;

	return true;
}

bool Tokenizer::initFromString(const Glib::ustring& str)
{
	m_buff = str;
	m_buff_pos = m_buff.begin();
	m_token.clear();
	m_last_delimiter = '\0';

	return true;
}

Glib::ustring Tokenizer::nextToken(void)
{
	m_token.clear();

	if (hasMoreTokens())
	{
		// Comprobamos si estamos en una cadena y hay que extraerla
		if ((*m_buff_pos == '"') && m_detect_strings)
		{
			m_token = getString();
			return m_token;
		}
		while ((m_buff_pos != m_buff.end()) && !isDelimiter())
		{
			m_token += *m_buff_pos;
			++m_buff_pos;
		}
	}
	return m_token;
}

bool Tokenizer::hasMoreTokens(void)
{
	m_last_delimiter_string.clear();
	// Saltamos delimitadores iniciales y guardamos el último y la cadena
	while ((m_buff_pos != m_buff.end()) && isDelimiter())
	{
		m_last_delimiter = *m_buff_pos;
		m_last_delimiter_string.push_back(m_last_delimiter);
		++m_buff_pos;
	}
	if (m_buff_pos != m_buff.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<Glib::ustring> Tokenizer::split(void)
{
	std::vector<Glib::ustring> tokens;

	while (hasMoreTokens())
	{
		tokens.push_back(nextToken());
	}

	return tokens;
}

Glib::ustring Tokenizer::getString(void)
{
	Glib::ustring str;

	// Saltamos las comillas iniciales donde hemos sido llamados
	++m_buff_pos;

	// Comprobamos caracteres escapados iniciales
	while (*m_buff_pos == '\\')
	{
		str += *m_buff_pos;
		++m_buff_pos;
		str += *m_buff_pos;
		++m_buff_pos;
	}

	// Consideramos que la cadena finaliza en " o al final del buffer
	while ((*m_buff_pos != '"') && (m_buff_pos != m_buff.end()) )
	{
		str += *m_buff_pos;
		++m_buff_pos;
		// Caracteres escapados internos
		while (*m_buff_pos == '\\')
		{
			str += *m_buff_pos;
			++m_buff_pos;
			str += *m_buff_pos;
			++m_buff_pos;
		}
	}

	// Si paramos en unas comillas, pasamos a la siguiente posición para evitar
	// que se vuelva a interpretar la posición como cadena
	if (*m_buff_pos == '"')
	{
		++m_buff_pos;
	}
	return str;
}
