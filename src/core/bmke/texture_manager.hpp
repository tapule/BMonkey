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

#ifndef _TEXTURE_MANAGER_HPP_
#define _TEXTURE_MANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <glibmm/ustring.h>
#include <unordered_map>
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Gestiona las texturas del sistema
 *
 * Se encarga de mantener y gestionar las texturas que serán usadas por el
 * frontend.
 * Actua como una especie de almacén para las texturas que se van cargando desde
 * fichero, proporcionando métodos para su carga y descarga.
 * Únicamente permite una instancia de la clase al mismo tiempo.
 */
class TextureManager
{
public:

	/**
	 * Constructor de la clase
	 */
	TextureManager(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~TextureManager(void);

	/**
	 * Carga una textura en el manager y la devuelve
	 * @param file Path del fichero de la textura
	 * @param repeated Indica si la textura se debe repetir en el eje x e y
	 * @return Textura cargada o null si no se pudo cargar
	 * @note Si la textura ya existe en el manager, no volverá a cargarla
	 * @note La lista de formatos de imagenes soportados es la siguiente: bmp,
	 * png, tga, jpg, gif, psd, hdr y pic. Algunas opciones de determinados
	 * formatos no son soportadas, como el jpeg progresivo
	 */
	sf::Texture* loadTexture(const Glib::ustring& file, const bool repeated = false);

	/**
	 * Devuelve una textura indexada por su fichero
	 * @param file Path del fichero de la textura
	 * @return Textura cargada o null si no se encuentra
	 */
	sf::Texture* getTexture(const Glib::ustring& file);

	/**
	 * Elimina una textura del almacen interno del manager
	 * @param file Path del fichero de la textura
	 */
	void deleteTexture(const Glib::ustring& file);

	/**
	 * Activa o desactiva el filtro de suavizado en las texturas
	 * @param smooth Indica si se debe activar o no el filtro
	 */
	void setSmooth(const bool smooth);

	/**
	 * Limpia TextureManager liberando todas las texturas cargadas
	 */
	void clean(void);

private:

	// Estructura para poder llevar el recuento de referencias de la textura
	struct Resource
	{
		unsigned int count;
		sf::Texture* texture;
	};

	static bool m_instantiated;		/**< Indica si ya hay una instancia de la clase */

	std::unordered_map<std::string, Resource > m_textures;	/**< Almacen de texturas */
	bool m_smooth;								/**< Indica si se debe aplicar suavizado a las texturas */
};

} // namespace bmonkey

#endif // _TEXTURE_MANAGER_HPP_
