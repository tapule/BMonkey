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

#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include <SFML/Graphics.hpp>
#include "../../defines.hpp"
#include "../../utils/config.hpp"

namespace bmonkey{

/**
 * Gestiona la ventana (pantalla) de graficos
 *
 * Se encarga de configurar y gestionar la ventana de renderizado sobre la que
 * dibujará la aplicación.
 * Únicamente permite una instancia de la clase al mismo tiempo.
 */
class Graphics
{
public:

	// Posibles rotaciones de la ventana
	enum Rotation
	{
		NONE = 0,
		RIGHT,
		INVERTED,
		LEFT
	};

	/**
	 * Constructor de la clase
	 * @param config Configuración de donde leer y escribir sus parámetros
	 */
	Graphics(Config* config);

	/**
	 * Destructor de la clase
	 */
	virtual ~Graphics(void);

	/**
	 * Inicializa los gráficos
	 */
	virtual void init(void);

	/**
	 * Establece una rotación determinada en la ventana
	 * @param rotation Nueva rotación para la ventana
	 */
	void rotate(const Rotation rotation);

	/**
	 * Cambia a la siguiente rotación de la pantalla
	 * @note El cambio de rotación se hace girandola a la derecha
	 */
	void switchRotation(void);

	/**
	 * Obtiene una captura de pantalla y la guarda en disco
	 */
	void capture(void);

	/**
	 * Obtiene la ventana de renderizado usada
	 * @return Ventana de renderizado usada
	 */
	sf::RenderWindow* getRenderWindow(void);

private:
	static bool m_instantiated;		/**< Indica si ya hay una instancia de la clase */

	bool m_init;					/**< Indica si se han inicializado los gráficos */
	Config* m_config;				/**< Sistema de configuración */
	Glib::ustring m_screenshot_dir;	/**< Path del directorio para guardar las capturas */
	sf::RenderWindow m_window;		/**< Ventana de renderizado */
	Rotation m_rotation;			/**< Rotación actual de la ventana */
};

} // namespace bmonkey

#endif // _GRAPHICS_HPP_
