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

#ifndef _GAMELIST_HPP_
#define _GAMELIST_HPP_

#include <glibmm/ustring.h>
#include <unordered_map>
#include <vector>
#include "game.hpp"
#include "filter.hpp"
#include "../../defines.hpp"

namespace bmonkey{

class Collection;

/**
 * Mantiene la información de una lista de juegos.
 *
 * Las listas de juegos actúan como contenedores para los juegos. Hay dos tipos
 * de listas:
 * - Master: Son listas que realmente contienen los datos de los juegos.
 * - Genérica: Son listas que únicamente tiene referencias a los juegos.
 */
class Gamelist
{
public:
	/**
	 * Constructor parametrizado
	 * @param collection Colección padre a la que pertenece la lista
	 * @param file Fichero donde residen los datos de los juegos
	 */
	Gamelist(Collection* collection, const Glib::ustring& file);

	/**
	 * Destructor de la clase
	 */
	virtual ~Gamelist(void);

	/**
	 * Obtiene el nombre de la lista
	 * @return Cadena de texto con el nombre de la lista
	 */
	inline Glib::ustring getName(void);

	/**
	 * Estable el nombre de la lista
	 * @param name Nuevo nombre para la lista
	 */
	inline void setName(const Glib::ustring& name);

	/**
	 * Indica si la lista es una lista Master
	 * @return true si es una lista master, false en otro caso
	 */
	inline bool isMaster(void);

	/**
	 * Establece si la lista es una lista Master o no
	 * @param is_master Nuevo valor para indicar el tipo de lista
	 */
	inline void setMaster(const bool is_master);

	/**
	 * Carga los juegos de la lista desde su fichero
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool loadGames(void);

	/**
	 * Guarda los juegos de la lista en su fichero
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveGames(void);

	/**
	 * Obtiene un juego a partir de su identificador
	 * @param id Identificador del juego requerido
	 * @return Juego buscado o Null si no se puede localizar
	 */
	Game* gameGet(int id);

	/**
	 * Añade un nuevo juego a la lista si no existe ya
	 * @param game Juego a añadir a la lista
	 * @return true si se pudo realizar la operación, false en otro caso
	 */
	bool gameAdd(Game* game);

	/**
	 * Elimina el juego indicado por su id de la lista
	 * @param id Identificador del juego a eliminar
	 * @return true si se pudo realizar la operación, false en otro caso
	 */
	bool gameDelete(int id);

	/**
	 * Elimina el juego indicado de la lista
	 * @param game Juego a eliminar
	 * @return true si se pudo realizar la operación, false en otro caso
	 */
	bool gameDelete(Game* game);

	/**
	 * Busca un juego en la lista mediante su set_name
	 * @param name Nombre de set del juego buscado
	 * @return Identificador del juego o -1 si no se pudo localizar
	 */
	int gameFind(const Glib::ustring& name);

	/**
	 * Obtiene el id del primer juego visible de la lista
	 * @return Identificador del juego o -1 si no se pudo localizar
	 */
	int gameFirst(void);

	/**
	 * Obtiene el id del siguiente juego visible a uno dado por su id
	 * @param id Identificado del juego del que se quiere obtener el siguiente
	 * @return id del siguiente juego visible o -1 si no se pudo localizar
	 * @note El recorrido de la lista se hace de manera circular
	 */
	int gameNext(int id);

	/**
	 * Obtiene el id del juego visible anterior a uno dado por su id
	 * @param id Identificado del juego del que se quiere obtener el anterior
	 * @return id del juego visible anterior o -1 si no se pudo localizar
	 * @note El recorrido de la lista se hace de manera circular*
	 */
	int gamePrevious(int id);

	/**
	 * Obtiene el id del último juego visible de la lista
	 * @return Identificador del juego o -1 si no se pudo localizar
	 */
	int gameLast(void);

	/**
	 * Obtiene el número de juegos disponibles en la lista
	 * @return Número de juegos de la lista
	 */
	inline int gameCount(void);

	/**
	 * Aplica a la lista de juegos una serie de filtros
	 * @param filters Vector de filtros a aplicar
	 */
	void filter(std::vector<Filter>& filters);

	/**
	 * Establece todos los juegos como visibles
	 */
	void unfilter(void);

private:
	/**
	 * Se encarga de limpiar los almacenes internos de los datos
	 */
	void clean(void);

	Collection* m_collection;			/**< Colección padre de la lista */
	Glib::ustring m_name;				/**< Nombre de la lista */
	Glib::ustring m_file;				/**< Fichero donde guardar y cargar los juegos */
	bool m_is_master;					/**< Indica si la lista es una lista master */

	std::unordered_map<std::string, Game*> m_games_map;	/**< Mapa de juegos para acceso rápido por nombre */
	std::vector<Game* > m_games;		/**< Vector de juegos para iteraciones rápidas */

};

} // namespace bmonkey

#endif // _GAMELIST_HPP_
