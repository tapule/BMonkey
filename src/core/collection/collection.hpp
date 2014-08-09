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

#ifndef _DB_MANAGER_HPP_
#define _DB_MANAGER_HPP_

#include <glibmm/ustring.h>
#include <unordered_map>
#include <vector>
#include "collection.hpp"
#include "../../defines.hpp"

namespace bmonkey{

/**
 */
class DbManager
{
public:
	/**
	 * Constructor parametrizado
	 * @param working_dir Directorio de trabajo
	 */
	DbManager(const Glib::ustring& working_dir){}

	/**
	 * Destructor de la clase
	 */
	virtual ~DbManager(void){}

	/**
	 * Carga el fichero principal con el listado de colecciones del sistema
	 * @return true si se pudo realizar la operación, falso en otro caso
	 * @note No se permiten coleciones duplicadas. Si se localizan se descartan
	 */
	bool loadConfig(void){}

	/**
	 * Carga las colecciones del sistema
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool loadCollections(void){}

	/**
	 * Guarda el fichero principal con el listado de colecciones del sistema
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveConfig(void){}

	/**
	 * Guarda los colecciones presentes en el sistema
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveCollections(void){}

	/**
	 * Obtiene una colección a partir de su identificador
	 * @param id Identificador de la colección requerida
	 * @return Colección buscada o Null si no se puede localizar
	 */
	Collection* collectiontGet(int id){}

	/**
	 * Busca una colección mediiante su nombre
	 * @param name Nombre de la colección buscada
	 * @return Colección buscada o Null si no se pudo localizar
	 */
	Collection* collectionFind(const Glib::ustring& name){}

	/**
	 * Crea una nueva colección
	 * @return Identificador de la nueva colección o -1 si no se pudo crear
	 * @note Permite crear colecciones que aun no han sido cargadas
	 */
	int collectionCreate(const Glib::ustring& name){}

	/**
	 * Elimina la colección indicada por su id
	 * @param id Identificador de la colección a eliminar
	 * @return true si se pudo realizar la operación, false en otro caso
	 */
	bool collectionDelete(int id){}

	/**
	 * Obtiene el id de la primera colección
	 * @return Identificador de la colección o -1 si no se pudo localizar
	 */
	int collectionFirst(void){}

	/**
	 * Obtiene el id de la siguiente colección a una dada por su id
	 * @param id Identificado de la colección de la que obtener su siguiente
	 * @return id de la siguiente colección o -1 si no se pudo localizar
	 * @note El recorrido de las colecciones se hace de manera circular
	 */
	int collectionNext(int id){}

	/**
	 * Obtiene el id de la colección anterior a una dada por su id
	 * @param id Identificado de la colección de la que obtener la anterior
	 * @return id de la colección anterior o -1 si no se pudo localizar
	 * @note El recorrido de las colecciones se hace de manera circular
	 */
	int collectionPrevious(int id){}

	/**
	 * Obtiene el id de la última colección
	 * @return Identificador de la última colección o -1 si no se pudo localizar
	 */
	int collectionLast(void){}

	/**
	 * Obtiene el número de listas de colecciones en el sistema
	 * @return Número de colecciones del sistema
	 */
	inline int collectionCount(void){}

private:
	Glib::ustring m_working_dir;	/**< Directorio de trabajo del gestor */
};

} // namespace bmonkey

#endif // _DB_MANAGER_HPP_
