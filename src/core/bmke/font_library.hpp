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

#ifndef _FONT_LIBRARY_HPP_
#define _FONT_LIBRARY_HPP_

#include <SFML/Graphics.hpp>
#include <glibmm/ustring.h>
#include <vector>
#include <unordered_map>
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Librería de fuentes para textos gráficos
 *
 * Se encarga de mantener y gestionar una librería de fuentes que serán usadas
 * por un consumidor.
 * Además de las fuentes cargadas por el usuario, proporciona una fuente por
 * defecto de sistema que siempre estará disponible y que se puede usar en
 * cualquier momento.
 */
class FontLibrary
{
public:
	/**
	 * Constructor de la clase
	 */
	FontLibrary(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~FontLibrary(void);

	/**
	 * Carga una fuente en la librería y la devuelve
	 * @param file Path del fichero de la fuente
	 * @return Fuente cargada o null si no se pudo cargar
	 * @note Si la fuente ya existe en el manager, no volverá a cargarla
	 * @note La lista de formatos de fuentes soportados es la siguiente:
	 * TrueType, Type 1, CFF, OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR y
	 * Type 42
	 */
	sf::Font* loadFont(const Glib::ustring& file);

	/**
	 * Obtiene la fuente del sistema
	 * @return Fuente del sistema o null en caso de error
	 */
	sf::Font* getSystemFont(void);

	/**
	 * Solicita a la librería que elimine una fuente cargada
	 * @param font Fuente que se quiere eliminar
	 */
	void deleteFont(sf::Font* font);

	/**
	 * Limpia la librería de fuentes liberando todas las cargadas
	 * @note Las fuentes del sistema nunca se descargan
	 */
	void clean(void);

private:

	// Estructura para poder llevar el recuento de referencias de la fuente
	struct Resource
	{
		Glib::ustring file;		/**< Path del fichero de la fuente */
		unsigned int count;		/**< Contador de referencias */
		sf::Font* font;			/**< Fuente real cargada */
	};

	std::vector<Resource> m_fonts;		/**< Almacen de fuentes del usuario */
	sf::Font m_system_font;				/**< Fuente del sistema */
};

} // namespace bmonkey

#endif // _FONT_LIBRARY_HPP_
