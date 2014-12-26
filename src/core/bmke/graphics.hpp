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
	 * Inicializa los gráficos y la ventana de renderizado
	 */
	virtual void init(void);

	/**
	 * Cierra la ventana de renderizado
	 */
	void close();

	/**
	 * Indica si la ventana de renderizado está abierta
	 * @return True si la ventana de renderizado está abierta
	 */
	bool isOpen() const;

	/**
	 * Obtiene las dimensiones de la ventana de renderizado, es decir, resolución
	 * @return Resolución de la ventana de renderizado
	 */
	sf::Vector2u getSize() const;

	/**
	 * Establece una rotación determinada en la ventana de renderizado
	 * @param rotation Nueva rotación para la ventana
	 */
	void rotate(const Rotation rotation);

	/**
	 * Cambia a la siguiente rotación de la ventana de renderizado
	 * @note El cambio de rotación se hace girandola a la derecha 90º
	 */
	void switchRotation(void);

	/**
	 * Obtiene una captura de pantalla y la guarda en disco
	 */
	void capture(void);

	/**
	 * Limpia la ventana de renderizado con un color específico
	 * @param color Color a usar para limpiar la ventana
	 */
	void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

	/**
	 * Dibuja un objeto Drawable en la ventana de renderizado
	 * @param drawable Objeto a dibujar
	 * @param states RenderStates a usar en el dibujado del objeto
	 */
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

	/**
	 * Muestra en pantalla lo que se ha dibujado en la ventana de renderizado
	 */
	void display();

	/**
	 * Obtiene la ventana de renderizado usada
	 * @return Ventana de renderizado usada
	 */
	sf::RenderWindow* getRenderWindow(void) const;

private:
	static bool m_instantiated;		/**< Indica si ya hay una instancia de la clase */

	Config* m_config;				/**< Sistema de configuración */
	Glib::ustring m_screenshot_dir;	/**< Path del directorio para guardar las capturas */
	sf::RenderWindow m_window;		/**< Ventana de renderizado */
	Rotation m_rotation;			/**< Rotación actual de la ventana */
};

// Inclusión de los métodos inline
#include "graphics.inl"

} // namespace bmonkey

#endif // _GRAPHICS_HPP_
