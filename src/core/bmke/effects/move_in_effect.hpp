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

#ifndef _MOVE_IN_EFFECT_HPP_
#define _MOVE_IN_EFFECT_HPP_

#include "../effect.hpp"

namespace bmonkey{

/**
 * Efecto base para animaciones de entrada en escena
 *
 * Los efectos de movimeinto de entrada en escena posicionan la entidad fuera de
 * la escena como inicio del efecto y luego aplican su animación hasta que la
 * entidad queda en su posición final.
 */
class MoveInEffect : public Effect
{
public:

	// Posibles posiciones de origen desde donde comenzar el efecto
	enum Origin
	{
		LEFT,		/**< El efecto comienza desde la izquierda de la pantalla */
		RIGHT,		/**< El efecto comienza desde la derecha de la pantalla */
		TOP,		/**< El efecto comienza desde la parte superior de la pantalla */
		BOTTOM		/**< El efecto comienza desde la parte inferior de la pantalla */
	};

	/**
	 * Constructor de la clase
	 */
	MoveInEffect(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~MoveInEffect(void);

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
	 * Establece la posición origen desde donde ejecutar el efecto
	 * @param from Nueva posición origen desde donde comenzar el efecto.
	 */
	void setOrigin(const Origin origin);

protected:
	sf::Vector2u m_win_size;/**< Tamaño de la ventana de referencia para los efectos */
	Origin m_origin;		/**< Posición origen desde donde comienza el efecto */
};

} // namespace bmonkey

#endif // _MOVE_IN_EFFECT_HPP_
