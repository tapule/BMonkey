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

#ifndef _COLLECTION_HPP_
#define _COLLECTION_HPP_

#include <glibmm/ustring.h>
#include <unordered_map>
#include <vector>
#include "../iterable.hpp"
#include "../../defines.hpp"
#include "platform.hpp"

namespace bmonkey{

/**
 * Mantiene la información completa de la colección de juegos del usuario.
 *
 * La Colección actua como contenedor para las Plataformas que el usuario tiene
 * configuradas.
 */
class Collection: public Iterable
{
public:
	/**
	 * Constructor parametrizado
	 * @param working_dir Directorio de trabajo
	 */
	Collection(const Glib::ustring& working_dir);

	/**
	 * Destructor de la clase
	 */
	virtual ~Collection(void);

	/**
	 * Carga el fichero principal con el listado de plataformas del usuario
	 * @return true si se pudo realizar la operación, falso en otro caso
	 * @note No se permiten plataformas duplicadas. Si se localizan se descartan
	 */
	bool loadConfig(void);

	/**
	 * Carga las plataformas del usuario
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool loadPlatforms(void);

	/**
	 * Guarda el fichero principal con el listado de plataformas del usuario
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveConfig(void);

	/**
	 * Guarda las plataformas del usuario
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool savePlatforms(void);

	/**
	 * Obtiene la lista de fabricantes de los juegos
	 * @return Vector de fabricantes de los juegos
	 */
	std::vector<Glib::ustring>& getManufacturers(void)
	{
		return m_manufactureres;
	}

	/**
	 * Obtiene la lista de géneros de los juegos
	 * @return Vector de géneros de los juegos
	 */
	std::vector<Glib::ustring>& getGenres(void)
	{
		return m_genres;
	}

	/**
	 * Obtiene una plataforma a partir de un item
	 * @param item Item a partir del cual obtener la plataforma
	 * @return Plataforma buscada o Null si no se puede localizar
	 */
	Platform* platformGet(Item* item);

	/**
	 * Obtiene una plataforma a partir de su nombre
	 * @param name Nombre de la plataforma buscada
	 * @return Plataforma buscada o Null si no se puede localizar
	 */
	Platform* platformGet(const Glib::ustring& name);

	/**
	 * Crea una nueva plataforma en la colección o la devuelve si existe
	 * @param name Nombre de la nueva plataforma
	 * @return Nueva plataforma creada o encontrada si existe, null si no se pudo crear
	 */
	Platform* platformCreate(const Glib::ustring& name);

	/**
	 * Obtiene el número de plataformas disponibles en la colección
	 * @return Número de plataformas en la colección
	 */
	int platformCount(void)
	{
		return m_size;
	}

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
	 * Añade una nueva plataforma a la lista si no existe ya
	 * @param platform Plataforma a añadir a la lista
	 * @return true si se pudo realizar la operación, false en otro caso
	 */
	bool platformAdd(Platform* platform);


	/**
	 * Genera las tablas de Fabricantes y Géneros a partir de los juegos
	 */
	void generateDinamicTables(void);

	/**
	 * Se encarga de limpiar los almacenes internos de los datos
	 */
	void clean(void);

	Glib::ustring m_working_dir;	/**< Directorio de trabajo principal */
	int m_size;						/**< Número de plataformas en la colección */
	Platform* m_first;				/**< Primera plataforma de la lista */
	Platform* m_last;				/**< Último plataforma de la lista */

	std::vector<Glib::ustring> m_manufactureres;	/**< Tabla de fabricantes */
	std::vector<Glib::ustring> m_genres;			/**< Tabla de géneros */
	std::unordered_map<std::string, Platform* > m_platforms_map;	/**< Mapa de plataformas para acceso rápido por nombre */
};

} // namespace bmonkey

#endif // _COLLECTION_HPP_
