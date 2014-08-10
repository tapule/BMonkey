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

#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <glibmm/ustring.h>

namespace bmonkey{

/**
 * Clase abstracta base para elementos que pueden ser iterados mediante
 * implementacionesla de Iterable.
 *
 * Un Item es una abstracción de un elemento que contiene información suficiente
 * para ser dibujado.
 */
class Item
{
public:

	/**
	 * Destructor virtual de la clase
	 */
	virtual ~Item(void){}

	/**
	 * Obtiene el nombre del item
	 * @return Cadena de texto con el nombre del item
	 */
	virtual Glib::ustring getName(void) = 0;

	/**
	 * Obtiene el titulo del item
	 * @return Cadena de texto con el titulo del item
	 */
	virtual Glib::ustring getTitle(void) = 0;

	/**
	 * Obtiene el directorio donde se almacenan los recursos del item
	 * @return Directorio de recursos del item
	 */
	virtual Glib::ustring getResourcesDir(void) = 0;
};

} // namespace bmonkey

#endif // _ITEM_HPP_
