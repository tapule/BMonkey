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

#ifndef _ANIMATION_FACTORY_HPP_
#define _ANIMATION_FACTORY_HPP_

#include "animation.hpp"

namespace bmonkey{

/**
 * Clase factory para las animaciones
 *
 * Dispone de un solo método estático que se encargará de crear una nueva
 * animación en función de su tipo.
 *
 */
class AnimationFactory
{
public:

	// Posibles tipos de animaciones
	enum Type
	{
		// Animaciones de entrada a escena
		LEFT_BACK_IN = 0,	/**< Animación de entrada Back desde la izquierda */
		RIGHT_BACK_IN,		/**< Animación de entrada Back desde la derecha */
		TOP_BACK_IN,		/**< Animación de entrada Back desde la parte superior */
		BOTTOM_BACK_IN,		/**< Animación de entrada Back desde la parte inferior */
		LEFT_BOUNCE_IN,		/**< Animación de entrada Bounce desde la izquierda */
		RIGHT_BOUNCE_IN,	/**< Animación de entrada Bounce desde la derecha */
		TOP_BOUNCE_IN,		/**< Animación de entrada Bounce desde la parte superior */
		BOTTOM_BOUNCE_IN,	/**< Animación de entrada Bounce desde la parte inferior */
		LEFT_EASE_IN,		/**< Animación de entrada Ease desde la izquierda */
		RIGHT_EASE_IN,		/**< Animación de entrada Ease desde la derecha */
		TOP_EASE_IN,		/**< Animación de entrada Ease desde la parte superior */
		BOTTOM_EASE_IN,		/**< Animación de entrada Ease desde la parte inferior */
		LEFT_ELASTIC_IN,	/**< Animación de entrada Elastic desde la izquierda */
		RIGHT_ELASTIC_IN,	/**< Animación de entrada Elastic desde la derecha */
		TOP_ELASTIC_IN,		/**< Animación de entrada Elastic desde la parte superior */
		BOTTOM_ELASTIC_IN,	/**< Animación de entrada Elastic desde la parte inferior */
		FADE_IN,			/**< Animación de entrada Fade */
		HARDROLL_IN,		/**< Animación de entrada HardRoll */
		POP_IN,				/**< Animación de entrada Pop */
		ROLL_IN,			/**< Animación de entrada Roll */
		ROTATE_IN,			/**< Animación de entrada Rotate */

		// Animaciones de salida de escena
		LEFT_BACK_OUT,		/**< Animación de salida Back hacia la izquierda */
		RIGHT_BACK_OUT,		/**< Animación de salida Back hacia la derecha */
		TOP_BACK_OUT,		/**< Animación de salida Back hacia la parte superior */
		BOTTOM_BACK_OUT,	/**< Animación de salida Back hacia la parte inferior */
		FADE_OUT,			/**< Animación de salida Fade */

		// Animaciones de posición en escena
		EASE_X,				/**< Animación de posición Ease sobre el eje X*/
		EASE_Y,				/**< Animación de posición Ease sobre el eje Y */
		FADE				/**< Animación de posición Fade */
	};

	/**
	 * Crea una animación dado su tipo y parámetros
	 * @param type Tipo de animación a crear
	 * @param delay Retardo inicial de la animación
	 * @param duration Duración de la animación
	 * @return Nueva animación creada
	 * @note El usuario debe encargarse de liberar la memoria ocupada por la
	 * animación devuelta por el método.
	 */
	static Animation* create(const Type type, const float delay, const float duration);

};

} // namespace bmonkey

#endif //_ANIMATION_FACTORY_HPP_
