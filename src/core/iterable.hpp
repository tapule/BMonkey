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

#ifndef _ITERABLE_HPP_
#define _ITERABLE_HPP_

#include <glibmm/ustring.h>
#include "item.hpp"

namespace bmonkey{

/**
 * Clase abstracta base que proporciona métodos para moverse por los Items en
 * clases que actúan como almacenes de items.
 */
class Iterable
{
public:

	/**
	 * Destructor virtual de la clase
	 */
	virtual ~Iterable(void){}

	/**
	 * Obtiene un item a partir de su nombre
	 * @param name Nombre del item a buscar
	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemGet(const Glib::ustring& name) = 0;

	/**
	 * Obtiene el primer item del almacen
	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemFirst(void) = 0;

	/**
	 * Obtiene el último item del almacen
	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemLast(void) = 0;

	/**
	 * Obtiene el siguiente item de uno dado
	 * @param item Elemento inicial del que buscar su siguiente
	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemNext(Item* item) = 0;

	/**
	 * Obtiene el item anterior de uno dado
	 * @param item Elemento inicial del que buscar su anterior
	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemPrev(Item* item) = 0;

	/**
	 * Obtiene el item a una distancia por delante, de otro item
	 * @param item Elemento inicial
	 * @param count Distancia adelante a la que moverse
	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemForward(Item* item, const int count) = 0;

	/**
	 * Obtiene el item a una distancia por detrás, de otro item
 	 * @param item Elemento inicial
	 * @param count Distancia atrás a la que moverse
 	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemBackward(Item* item, const int count) = 0;

	/**
	 * Obtiene el item cuyo título comienza con la siguiente inicial a uno dado
 	 * @param item Elemento inicial
	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemLetterForward(Item* item) = 0;

	/**
	 * Obtiene el item cuyo título comienza con la inicial anterior a uno dado
 	 * @param item Elemento inicial
	 * @return Item buscado o null si no se localizó
	 */
	virtual Item* itemLetterBackward(Item* item) = 0;
};

} // namespace bmonkey

#endif // _ITERABLE_HPP_
