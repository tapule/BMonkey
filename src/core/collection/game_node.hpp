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

#ifndef _GAME_NODE_HPP_
#define _GAME_NODE_HPP_

#include <glibmm/ustring.h>
#include <cassert>
#include "../item.hpp"
#include "game.hpp"

namespace bmonkey{

/**
 * Nodo contenedor de la información de un juego
 *
 * Permite mantener varios nodos de las listas de juegos apuntando al mismo
 * juego, de este modo se facilita el uso de una una lista de juegos master que
 * contiene los juegos reales y listas que son simples apuntadores a los juegos
 * reales.
 */
class GameNode: public Item
{
public:
	/**
	 * Constructor de la clase
	 */
	GameNode(void):
		m_next(NULL),
		m_prev(NULL),
		m_next_filtered(NULL),
		m_prev_filtered(NULL),
		m_game(NULL)
	{
	}

	/**
	 * Destructor virtual de la clase
	 */
	virtual ~GameNode(void)	{}

	/**
	 * Obtiene el siguiente nodo enlazado
	 * @return Siguiente nodo enlazado
	 */
	GameNode* getNext(void);

	/**
	 * Establece el siguiente nodo enlazado
	 * @param next Siguiente nodo a enlazar
	 */
	void setNext(GameNode* next);

	/**
	 * Obtiene el nodo previo enlazado
	 * @return Nodo Previo
	 */
	GameNode* getPrev(void);

	/**
	 * Establece el nodo previo enlazado
	 * @param prev Nodo previo a enlazar
	 */
	void setPrev(GameNode* prev);

	/**
	 * Obtiene el siguiente nodo enlazado filtrado
	 * @return Siguiente nodo filtrado
	 */
	GameNode* getNextFiltered(void);

	/**
	 * Establece el siguiente nodo filtrado
	 * @param next Siguiente nodo filtrado a enlazar
	 */
	void setNextFiltered(GameNode* next);

	/**
	 * Obtiene el nodo previo enlazado filtrado
	 * @return Nodo previo filtrado
	 */
	GameNode* getPrevFiltered(void);

	/**
	 * Establece el nodo previo filtrado
	 * @param prev Nodo previo filtrado a enlazar
	 */
	void setPrevFiltered(GameNode* prev);

	/**
	 * Obtiene el juego almacenado en el nodo
	 * @return Juego almacenado
	 */
	Game* getGame(void);

	/**
	 * Fija el juego que se almacena en el nodo
	 * @param game Nuevo juego a almacenar en el nodo
	 */
	void setGame(Game* game);

	// Implementación de Item
	/**
	 * Obtiene el nombre del juego almacenado en el nodo
	 * @return Cadena de texto con el nombre del juego
	 */
	Glib::ustring itemName(void);

	/**
	 * Obtiene el titulo del juego almacenado en el nodo
	 * @return Cadena de texto con el titulo del juego
	 */
	Glib::ustring itemTitle(void);

	/**
	 * Obtiene el directorio donde se almacenan los recursos del juego del nodo
	 * @return Directorio de recursos del juego
	 */
	Glib::ustring itemResourcesDir(void);

protected:
	GameNode* m_next;			/**< Siguiente nodo de la lista */
	GameNode* m_prev;			/**< Nodo previo en la lista */
	GameNode* m_next_filtered;	/**< Siguiente nodo de la lista filtrada */
	GameNode* m_prev_filtered;	/**< Nodo previo de la lista filtrada */
	Game* m_game;				/**< Juego almacenado por el nodo */
};

// Inclusión de los métodos inline
#include "game_node.inl"

} // namespace bmonkey

#endif // _GAME_NODE_HPP_
