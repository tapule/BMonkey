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

#ifndef _FONT_MANAGER_HPP_
#define _FONT_MANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <glibmm/ustring.h>
#include <vector>
#include <unordered_map>
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Gestiona las fuentes de texto del sistema
 *
 * Se encarga de mantener y gestionar las fuentes que serán usadas por el
 * frontend.
 * Proporciona unas fuentes del sistema que siempre están activas y que se
 * pueden usar en cualquier momento y otras fuentes cargadas y descargadas por
 * el usuario.
 * Se define como singleton, de forma que solamente tendrémos una instancia
 * durante toda la ejecución.
 */
class FontManager
{
public:

	// Fuentes especiales del fe, siempre permanecen cargadas
	enum SystemFonts
	{
		DEFAULT = 0,	/**< Fuente por defecto usada en los mensajes del fe */
		SYMBOLS,		/**< Fuente especial con simbolos usados por el fe */
		COUNT			/**< Contador de fuentes del sistema */
	};

protected:
	/**
	 * Constructor de la clase
	 */
	FontManager(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~FontManager(void);

	/**
	 * Constructor de copia anulado para reforzar el singleton
	 */
	FontManager(FontManager const&);

	/**
	 * Operador de copia anulado para reforzar el singleton
	 */
	FontManager& operator=(FontManager const&);

public:
	/**
	 * Obtiene la instancia única del manager
	 * @return Instancia única del manager
	 */
	static FontManager* getInstance(void);

	/**
	 * Carga una fuente en el manager y la devuelve
	 * @param file Path del fichero de la fuente
	 * @return Fuente cargada o null si no se pudo cargar
	 * @note Si la fuente ya existe en el manager, no volverá a cargarla
	 * @note La lista de formatos de fuentes soportados es la siguiente:
	 * TrueType, Type 1, CFF, OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR y
	 * Type 42
	 */
	sf::Font* loadFont(const Glib::ustring& file);

	/**
	 * Devuelve una fuente indexada por su fichero
	 * @param file Path del fichero de la fuente
	 * @return Fuente cargada o null si no se encuentra
	 */
	sf::Font* getFont(const Glib::ustring& file);

	/**
	 * Obtiene una fuente del sistema
	 * @param id Identificador de la fuente del sistema solicitada
	 * @return Fuente solicitada o null en caso de error
	 */
	sf::Font* getSystemFont(const SystemFonts id);

	/**
	 * Elimina una fuente del almacen interno del manager
	 * @param file Path del fichero de la fuente
	 */
	void deleteFont(const Glib::ustring& file);

	/**
	 * Limpia FontManager liberando todas las fuentes cargadas
	 * @note Las fuentes del sistema nunca se descargan
	 */
	void clear(void);

private:

	// Estructura para poder llevar el recuento de referencias de la fuente
	struct Resource
	{
		unsigned int count;
		sf::Font* font;
	};

	std::vector<sf::Font> m_system_fonts;				/**< Almacen de fuentes del sistema */
	std::unordered_map<std::string, Resource > m_fonts; /**< Almacen de fuentes del usuario */

	static FontManager* m_font_manager; 				/**< Instancia única del manager */
};

} // namespace bmonkey

#endif // _FONT_MANAGER_HPP_
