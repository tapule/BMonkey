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

#ifndef _MOVE_OUT_EFFECT_HPP_
#define _MOVE_OUT_EFFECT_HPP_

#include "../effect.hpp"

namespace bmonkey{

/**
 * Efecto base para animaciones de salida de escena
 *
 * Los efectos de movimiento de salida de escena comienzan en la posición actual
 * de la entidad como inicio del efecto y aplican su animación hasta que la
 * entidad queda totalmente fuera de la escena.
 */
class MoveOutEffect : public Effect
{
public:

	// Posibles posiciones de destino donde terminar el efecto
	enum Destination
	{
		LEFT,		/**< El efecto terminará a la izquierda de la pantalla */
		RIGHT,		/**< El efecto terminará a la derecha de la pantalla */
		TOP,		/**< El efecto terminará sobre la parte superior de la pantalla */
		BOTTOM		/**< El efecto terminará bajo la parte inferior de la pantalla */
	};

	/**
	 * Constructor de la clase
	 */
	MoveOutEffect(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~MoveOutEffect(void);

	/**
	 * Inicializa el efecto asignando sus parámetros de procesado
	 * @param entity Entidad sobre la que actuará el efecto
	 * @param delay Retraso en segundos antes de comenzar el procesado
	 * @param duration Duración del efecto en segundos
	 */
	virtual void init(Entity* entity, const float delay, const float duration);

	/**
	 * Establece las dimensiones de la ventana de referencia donde aplicar el efecto
	 * @param win_size Tamaño de la ventana de referencia sobre la que se ejecuta el efecto
	 */
	void setWindowSize(const sf::Vector2u& win_size);

	/**
	 * Obtiene las dimensiones de la ventana de referencia
	 * @return Dimensiones de la ventana de referencia
	 */
	sf::Vector2u getWindowSize(void) const;

	/**
	 * Establece la posición final del efecto
	 * @param to Nueva posición final para el efecto.
	 */
	void setDestination(const Destination destination);

	/**
	 * Obtiene la posición final del efecto
	 * @return Posición final donde quedará el efecto
	 */
	Destination getDestination(void) const;

	/**
	 * Obtiene la posición final calculada para el efecto
	 * @return Posición final calculada para el efecto
	 */
	float getFinalPosition(void) const;

private:
	sf::Vector2u m_win_size;	/**< Tamaño de la ventana de referencia para los efectos */
	Destination m_destination;	/**< Posición final del efecto */
	float m_final_pos;			/**< Coordenada final del efecto */
};

// Inclusión de los métodos inline
#include "move_out_effect.inl"

} // namespace bmonkey

#endif // _MOVE_OUT_EFFECT_HPP_
