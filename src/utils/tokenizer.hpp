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

#ifndef _TOKENIZER_HPP_
#define _TOKENIZER_HPP_

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif /* HAVE_CONFIG_H */

// Si no está definido el modo debug, desactivamos los asserts
#ifndef ENABLE_DEBUG_MODE
	#define NDEBUG
#endif

#include <cassert>
#include <vector>
#include <glibmm/ustring.h>


// Delimitadores por defecto: Espacio, Salto de línea, Retorno de carro,
// Tabulador horizontal, Tabulador vertical y Avance de página
static const Glib::ustring DEFAULT_DELIMITERS = " \n\r\t\v\f";

/**
 * Tokenizador de cadenas simple con soporte para UTF-8.
 *
 * Permite trocear cadenas de texto o el contenido de un fichero en sus
 * sub-bloques.
 * Permite establecer los caracteres que se detectarán como delimitadores. Por
 * defecto detecta como delimitadores los caracteres Espacio, Salto de línea,
 * Retorno de carro, Tabulador horizontal, Tabulador vertical y Avance de
 * página.
 * Incluye soporte para detectar cadenas de texto entrecomilladas activado por
 * defecto.
 */
class Tokenizer
{
public:
	/**
	 * Constructor básico de la clase.
	 */
	Tokenizer(void);

	/**
	 * Constructor parametrizado
	 * @param delimiters Delimitadores a usar por defecto
	 * @param detect_str Indica si se deben detectar las cadenas de texto
	 */
	Tokenizer(const Glib::ustring& delimiters, const bool detect_str = true);

	/**
	 * Destructor
	 */
	~Tokenizer();

	/**
	 * Inicializa el tokenizador a partir de un buffer de memoria
	 * @param buffer Puntero al buffer donde se almacenan los datos
	 * @param size Tamaño total del buffer
	 * @return true si se realizó la carga correctamente
	 */
	bool initFromMemory(const char *buffer, const unsigned int size);

	/**
	 * Inicializa el tokenizador sobre un fichero determinado
	 * @param file nombre del fichero con el contenido a tokenizar
	 * @return true si se realizó la carga correctamente
	 */
	bool initFromFile(const Glib::ustring& file);

	/**
	 * Inicializa el tokenizador sobre una cadena de texto
	 * @param str Cadena de texto a tokenizar
	 * @return true si se realizó la carga correctamente
	 */
	bool initFromString(const Glib::ustring& str);

	/**
	 * Establece los delimitadores que debe reconocer el tokenizador para
	 * separar tokens. Los delimitadores por defecto son ' ', '\n', '\r', '\t',
	 * '\v', \f'
	 * @param delimiters Nuevos delimitadores a usar por el tokenizador
	 * @note El tokenizador continuará por donde estaba, para comenzar de nuevo
	 * con los nuevos delimitadores, usar reset()
	 */
	void setDelimiters(const Glib::ustring& delimiters);

	/**
	 * Activa o desactiva la detección de cadenas en el tokenizador.
	 * Se consideran cadenas las siguientes: "..." ó "...\0
	 * @param detect true para activar la detección, false para desactivarla
	 */
	void setStringDetection(const bool detect = true);

	/**
	 * Obtiene el siguiente token
	 * @return Token leído o "" si no quedan más tokens
	 */
	Glib::ustring nextToken(void);

	/**
	 * Indica si quedan tokens por leer en el tokenizador
	 * @return true si quedan más tokens por leer
	 * @note Posiciona la lectura en el comienzo del siguiente token valido
	 */
	bool hasMoreTokens(void);

	/**
	 * Obtiene el último delimitador encontrado durante el proceso
	 * @return Carácter delimitador detectado en formato UTF-8
	 */
	Glib::ustring::value_type lastDelimiter(void);

	/**
	 * Obtiene la ultima cadena de delimitador encontrada durante el proceso
	 * @return Cadena de delimitadores contiguos detectada
	 * @note Este método es útil para hacer reconstrucciones del texto original
	 * pero con procesado de los tokens.
	 */
	Glib::ustring lastDelimiterString(void);

	/**
	 * Resetea el tokenizador para comenzar el proceso de nuevo
	 */
	void reset(void);

	/**
	 * Obtiene todos los tokens restantes de golpe
	 * @return Vector con los tokens restantes
	 */
	std::vector<Glib::ustring> split(void);

private:

	/**
	 * Comprueba si la posición de lectura del buffer está sobre un delimitador
	 * @return true si se encontró un delimitador, false en otro caso
	 */
	bool isDelimiter(void);

	/**
	 * Obtiene una cadena del buffer del tokenizador
	 * @return cadena leída
	 * @note Se consideran cadenas las siguientes: "..." ó "...\0
	 * @note trata entidades como un solo caracter (\t, \n, etc)
	 */
	Glib::ustring getString(void);

	Glib::ustring m_buff;						/**< Buffer del tokenizador */
	Glib::ustring::const_iterator m_buff_pos;	/**< Posición de lectura del buffer */
	Glib::ustring m_delimiters;					/**< Lista de delimitadores */
	Glib::ustring m_token;						/**< Token leído */
	Glib::ustring::value_type m_last_delimiter;	/**< Ultimo delimitador encontrado */
	Glib::ustring m_last_delimiter_string;		/**< Ultima cadena de delimitadores encontrada */
	bool m_detect_strings;						/**< Estado de la detección de cadenas */
};

// Inclusión de los métodos inline
#include "tokenizer.inl"

#endif // _TOKENIZER_HPP_
