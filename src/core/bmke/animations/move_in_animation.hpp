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

#ifndef _MOVE_IN_ANIMATION_HPP_
#define _MOVE_IN_ANIMATION_HPP_

#include "../animation.hpp"

namespace bmonkey{

/**
 * Animación base para la entrada/aparición de entidades en escena
 *
 * Las animaciones de movimeinto de entrada en escena posicionan la entidad
 * fuera de la escena como inicio de la animación y luego aplican su transición
 * hasta que la entidad queda en su posición final.
 */
class MoveInAnimation : public Animation
{
public:

	// Posibles posiciones de origen desde donde comenzar la animación
	enum Origin
	{
		LEFT,		/**< La animación comienza desde la izquierda de la pantalla */
		RIGHT,		/**< La animación comienza desde la derecha de la pantalla */
		TOP,		/**< La animación comienza desde la parte superior de la pantalla */
		BOTTOM		/**< La animación comienza desde la parte inferior de la pantalla */
	};

	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial de la animación
	 * @param duration Duración de la animación
	 */
	MoveInAnimation(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~MoveInAnimation(void);

	/**
	 * Inicializa la animación para una entidad determinada
	 * @param entity Entidad sobre la que actuará la animación
	 */
	virtual void init(Entity* entity);

	/**
	 * Comienza el procesado de la animación desde su inicio
	 */
	virtual void run(void) = 0;

	/**
	 * Detiene el procesado de la animación dejando la entidad en su estado inicial
	 */
	virtual void stop(void);

	/**
	 * Actualiza el estado de la animación
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time) = 0;

	/**
	 * Establece las dimensiones de la ventana de referencia donde aplicar la animación
	 * @param win_size Tamaño de la ventana de referencia sobre la que se ejecuta la animación
	 */
	void setWindowSize(const sf::Vector2u& win_size);

	/**
	 * Obtiene las dimensiones de la ventana de referencia
	 * @return Dimensiones de la ventana de referencia
	 */
	sf::Vector2u getWindowSize(void) const;

	/**
	 * Establece la posición origen desde donde ejecutar la animación
	 * @param from Nueva posición origen desde donde comenzar la animación.
	 */
	void setOrigin(const Origin origin);

	/**
	 * Obtiene la posición origen desde donde ejecutar la animación
	 * @return Posición origen desde donde comenzar la animación
	 */
	Origin getOrigin(void) const;

protected:
	sf::Vector2f m_entity_pos;	/**< Posición inicial de la entidad */
	sf::Vector2f m_start_pos;	/**< Posición inicial de la animación */

private:
	sf::Vector2u m_win_size;/**< Tamaño de la ventana de referencia para la aniamción */
	Origin m_origin;		/**< Posición origen desde donde comienza la animación */
};

// Inclusión de los métodos inline
#include "move_in_animation.inl"

} // namespace bmonkey

#endif // _MOVE_IN_ANIMATION_HPP_
