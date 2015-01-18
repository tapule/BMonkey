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

#ifndef _MOVE_OUT_ANIMATION_HPP_
#define _MOVE_OUT_ANIMATION_HPP_

#include "../animation.hpp"

namespace bmonkey{

/**
 * Animación base para la salida/desaparición de entidades en escena
 *
 * Las animaciones de movimeinto de salida de escena comienzan en la posición
 * actual de la entidad como inicio de la animación y aplican su transición
 * hasta que la entidad queda totalmente fuera de la escena.
 */
class MoveOutAnimation : public Animation
{
public:

	// Posibles posiciones de destino donde terminar la animación
	enum Destination
	{
		LEFT,		/**< La animación terminará a la izquierda de la pantalla */
		RIGHT,		/**< La animación terminará a la derecha de la pantalla */
		TOP,		/**< La animación terminará sobre la parte superior de la pantalla */
		BOTTOM		/**< La animación terminará bajo la parte inferior de la pantalla */
	};

	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial de la animación
	 * @param duration Duración de la animación
	 */
	MoveOutAnimation(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~MoveOutAnimation(void);

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
	 * Establece la posición final de la animación
	 * @param to Nueva posición final para la animación
	 */
	void setDestination(const Destination destination);

	/**
	 * Obtiene la posición final de la animación
	 * @return Posición final donde quedará la animación
	 */
	Destination getDestination(void) const;

protected:
	sf::Vector2f m_entity_pos;	/**< Posición inicial de la entidad */
	sf::Vector2f m_dest_pos;	/**< Posición destino de la animación */

private:
	sf::Vector2u m_win_size;	/**< Tamaño de la ventana de referencia para la animación */
	Destination m_destination;	/**< Posición final de la animación */
};

// Inclusión de los métodos inline
#include "move_out_animation.inl"

} // namespace bmonkey

#endif // _MOVE_OUT_ANIMATION_HPP_
