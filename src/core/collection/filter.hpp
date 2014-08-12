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

#ifndef _FILTER_HPP_
#define _FILTER_HPP_

#include <glibmm/ustring.h>

namespace bmonkey{

/**
 * Mantiene la información de un filtro y su valor.
 */
struct Filter
{
	// Posibles filtros para las listas de juegos
	enum Type{
		SEARCH = 0,			/**< Filtro para búsquedas */
		FAVORITE,			/**< Filtro por favorito */
		TYPE,				/**< Filtro por tipo de juego (original, clon, bios) */
		MANUFACTURER,		/**< Filtro por fabricante */
		YEAR,				/**< Filtro por año */
		GENRE,				/**< Filtro por género */
		PLAYERS,			/**< Filtro por núemro de juegadores */
		SIMULTANEOUS,		/**< Filtro por juegadores simultaneos*/
		RATING,				/**< Filtro por puntuación */
		LETTER,				/**< Filtro por letra inicial */
		TIMES_PLAYED,		/**< Filtro por partidas jugadas */
		COUNT				/**< Contador de filtros */
	};

	/**
	 * Constructor básico
	 */
	Filter(void):
		type(SEARCH),
		value(0)
	{
	}

	/**
	 * Constructor parametrizado para filtros numéricos
	 * @param p_type Nuevo tipo de filtro
	 * @param p_value Valor para el filtro
	 */
	Filter(const Type p_type, const long long int p_value):
		type(p_type),
		value(p_value)
	{
	}

	/**
	 * Constructor parametrizado para filtros de texto
	 * @param p_type Nuevo tipo de filtro
	 * @param p_value Valor para el filtro
	 */
	Filter(const Type p_type, const Glib::ustring& p_value):
		type(p_type),
		value(0),
		value_txt(p_value)
	{
	}

	Type type;					/**< Tipo de filtro */
	long long int value;		/**< Valor del filtro para filtros numéricos */
	Glib::ustring value_txt;	/**< Valor del filtro para filtros de texto*/
};

} // namespace bmonkey

#endif /* _FILTER_HPP_ */
