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
#include <glibmm/regex.h>
#include <unordered_map>
#include "../iterable.hpp"
#include "filter.hpp"
#include "../../defines.hpp"
#include "game_node.hpp"

namespace bmonkey{

/**
 * Mantiene la información de una lista de juegos.
 *
 * Las listas de juegos actúan como contenedores para los juegos. Hay dos tipos
 * de listas:
 * - Master: Son listas que realmente contienen los datos de los juegos.
 * - Genérica: Son listas que únicamente tienen referencias a los juegos.
 * Los juegos se mantienen en Nodos, de forma que multiples listas pueden
 * compartir los mismos juegos reales.
 */
class Gamelist: public Iterable
{
public:
	/**
	 * Constructor parametrizado
	 * @param name Nombre de la lista de juegos
	 * @param resources_dir Directorio de recursos de la plataforma padre
	 * @param master Lista master para los juegos de esta lista
	 */
	Gamelist(const Glib::ustring& name, Glib::ustring& resources_dir, Gamelist* master);

	/**
	 * Destructor de la clase
	 */
	virtual ~Gamelist(void);

	/**
	 * Obtiene el nombre de la lista
	 * @return Cadena de texto con el nombre de la lista
	 */
	Glib::ustring getName(void);

	/**
	 * Indica si la lista es una lista Master
	 * @return true si es una lista master, false en otro caso
	 */
	bool isMaster(void);

	/**
	 * Establece si la lista es una lista Master o no
	 * @param is_master Nuevo valor para indicar el tipo de lista
	 */
	void setMaster(const bool is_master);

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
	 * Aplica a la lista de juegos una pila de filtros
	 * @param filters Pila de filtros a aplicar
	 * @note La pila de filtros es un vector de tamaño Filter::COUNT donde cada
	 * ínidice identifica al tipo de filtro a aplicar
	 */
	void filter(std::vector<Filter* >& filters);

	/**
	 * Indica si la lista está filtrada
	 * @return true si la lista está filtrada, false en otro caso
	 */
	bool isFiltered(void);

	/**
	 * Establece todos los juegos como visibles
	 */
	void unfilter(void);

	/**
	 * Añade un nuevo juego a la lista si no existe ya
	 * @param game Juego a añadir a la lista
	 * @return true si se pudo realizar la operación, false en otro caso
	 */
	bool gameAdd(Game* game);

	/**
	 * Obtiene un juego a partir de un item
	 * @param item Item a partir del cual obtener el juego
	 * @return Juego buscado o Null si no se puede localizar
	 */
	Game* gameGet(Item* item);

	/**
	 * Obtiene un juego a partir de su nombre de set
	 * @param name Nombre de set del juego buscado
	 * @return Juego buscado o Null si no se puede localizar
	 */
	Game* gameGet(const Glib::ustring& name);

	/**
	 * Elimina el juego indicado por su nombre de set
	 * @param name Nombre del juego a eliminar
	 * @return true si se pudo realizar la operación, false en otro caso
	 */
	bool gameDelete(const Glib::ustring& name);

	/**
	 * Obtiene el número de juegos disponibles en la lista
	 * @return Número de juegos de la lista
	 */
	int gameCount(void);

	/**
	 * Obtiene el número de juegos disponibles en la lista filtrada
	 * @return Número de juegos de la lista filtrada
	 */
	int gameCountFiltered(void);

	// Implementación de Iterable
	/**
	 * Obtiene un item a partir de su nombre
	 * @param name Nombre del item a buscar
	 * @return Item buscado o null si no se localizó
	 */
	Item* itemGet(const Glib::ustring& name);

	/**
	 * Obtiene el primer item del almacen
	 * @return Item buscado o null si no se localizó
	 */
	Item* itemFirst(void);

	/**
	 * Obtiene el último item del almacen
	 * @return Item buscado o null si no se localizó
	 */
	Item* itemLast(void);

	/**
	 * Obtiene el siguiente item de uno dado
	 * @param item Elemento inicial del que buscar su siguiente
	 * @return Item buscado o null si no se localizó
	 */
	Item* itemNext(Item* item);

	/**
	 * Obtiene el item anterior de uno dado
	 * @param item Elemento inicial del que buscar su anterior
	 * @return Item buscado o null si no se localizó
	 */
	Item* itemPrev(Item* item);

	/**
	 * Obtiene el item a una distancia por delante, de otro item
	 * @param item Elemento inicial
	 * @param count Distancia adelante a la que moverse
	 * @return Item buscado o null si no se localizó
	 */
	Item* itemForward(Item* item, const int count);

	/**
	 * Obtiene el item a una distancia por detrás, de otro item
 	 * @param item Elemento inicial
	 * @param count Distancia atrás a la que moverse
 	 * @return Item buscado o null si no se localizó
	 */
	Item* itemBackward(Item* item, const int count);

	/**
	 * Obtiene el item cuyo título comienza con la siguiente inicial a uno dado
 	 * @param item Elemento inicial
	 * @return Item buscado o null si no se localizó
	 */
	Item* itemLetterForward(Item* item);

	/**
	 * Obtiene el item cuyo título comienza con la inicial anterior a uno dado
 	 * @param item Elemento inicial
	 * @return Item buscado o null si no se localizó
	 */
	Item* itemLetterBackward(Item* item);

private:

	/**
	 * Aplica a un nodo un vector de filtros
	 * @param node Nodo al que aplicar los filtros
	 * @param filters Vector de filtros a aplicar
	 * @return True si el nodo es visible tras los filtros, false en otro caso
	 */
	bool applyFilters(GameNode* node, std::vector<Filter* >& filters);

	/**
	 * Obtiene un nodo buscandolo por su nombre
	 * @param name Nombre de set del nodo
	 * @return Nodo buscado o null si no se encuentra
	 */
	GameNode* nodeGet(const Glib::ustring& name);

	/**
	 * Se encarga de limpiar los almacenes internos de los datos
	 */
	void clean(void);

	Glib::ustring& m_resources_dir;		/**< Referencia al directorio de recursos */
	Gamelist* m_master;
	Glib::ustring m_name;				/**< Nombre de la lista */
	Glib::ustring m_file;				/**< Fichero donde guardar y cargar los juegos */
	bool m_is_master;					/**< Indica si la lista es una lista master */
	bool m_is_filtered;					/**< Indica si la lista estafiltrada */
	int m_size;							/**< Número de elementos de la lista */
	int m_size_filtered;				/**< Número de elementos de la lista filtrada */

	GameNode* m_first;					/**< Primer elemento de la lista */
	GameNode* m_last;					/**< Último elemento de la lista */
	GameNode* m_first_filtered;			/**< Primer elemento filtrado de la lista */
	GameNode* m_last_filtered;			/**< Último elemento filtrado de la lista */

	std::unordered_map<std::string, GameNode*> m_games_map;	/**< Mapa de juegos para acceso rápido por nombre */

	Glib::RefPtr<Glib::Regex> m_regex;	/**< Expresión regular para el filtrado por nombre */
};

// Inclusión de los métodos inline
#include "gamelist.inl"

} // namespace bmonkey

#endif // _GAMELIST_HPP_
