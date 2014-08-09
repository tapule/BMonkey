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

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <glibmm/ustring.h>

namespace bmonkey{

// Posibles tipos de juegos
enum GameType
{
	GAME_TYPE_UNKNOWN = 0,		/**< Tipo desconocido */
	GAME_TYPE_ORIGINAL,			/**< Juego original */
	GAME_TYPE_CLONE,			/**< Juego clon */
	GAME_TYPE_BIOS				/**< Bios */
};

// Posibles estados de un juego
enum GameState
{
	GAME_STATE_UNKNOWN = 0,		/**< Estado desconocido (no comprobado) */
	GAME_STATE_CORRECT,			/**< Estado correcto (comprobado y localizado) */
	GAME_STATE_INCORRECT		/**< Estado incorrecto (comprobado y no localizado) */
};

class Collection;

/**
 * Mantiene la información de un juego.
 */
struct Game
{
	/**
	 * Constructor básico
	 */
	Game(void):
		collection(NULL),
		enabled(true),
		state(GAME_STATE_UNKNOWN),
		type(GAME_TYPE_UNKNOWN),
		players(0),
		simultaneous(false),
		rating(0),
		times_played(0),
		favorite(false)
	{
	}

	/**
	 * Constructor parametrizado
	 */
	Game(Collection* p_collection):
		collection(p_collection),
		enabled(true),
		state(GAME_STATE_UNKNOWN),
		type(GAME_TYPE_UNKNOWN),
		players(0),
		simultaneous(false),
		rating(0),
		times_played(0),
		favorite(false)
	{
	}

	Collection* collection;			/**< Colección padre del juego */
	Glib::ustring name;				/**< Nombre de set del juego */
	bool enabled;					/**< Indica si el juego está habilitado o no */

	GameState state;				/**< Estado del juego (0 desconocido, 1 lcorrecto, 2 incorrecto) */

	GameType type;					/**< Indica el tipo del set (original, clon, bios) */
	Glib::ustring crc;				/**< CRC asignado al juego (de su rom) */

	Glib::ustring title;			/**< Título del juego */
	Glib::ustring manufacturer;		/**< Fabricante del juego */
	Glib::ustring year;				/**< Año de lanzamiento */
	Glib::ustring genre;			/**< Género del juego */
	int players;					/**< Número de jugadores del juego, 0 para desconocido */
	bool simultaneous;				/**< Indica si los jugadores pueden jugar simultáneamente o no */

	int rating;						/**< Puntuación del juego*/
	unsigned int times_played;		/**< Contador de veces jugado */
	bool favorite;					/**< Indica si el juego está marcado como favorito */
};

} // namespace bmonkey

#endif // _GAME_HPP_
