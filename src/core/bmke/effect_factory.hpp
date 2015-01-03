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

#ifndef _EFFECT_FACTORY_HPP_
#define _EFFECT_FACTORY_HPP_

#include "effect.hpp"

namespace bmonkey{

/**
 * Clase factory para efectos
 *
 * Dispone de un solo método estático que se encargará de crear el nuevo efecto
 * en función de su tipo.
 *
 */
class EffectFactory
{
public:

	// Posibles tipos de efecto
	enum Type
	{
		// Efectos de entrada a escena
		BACK_IN = 0,		/**< Efecto de entrada Back genérico */
		LEFT_BACK_IN,		/**< Efecto de entrada Back desde la izquierda */
		RIGHT_BACK_IN,		/**< Efecto de entrada Back desde la derecha */
		TOP_BACK_IN,		/**< Efecto de entrada Back desde la parte superior */
		BOTTOM_BACK_IN,		/**< Efecto de entrada Back desde la parte inferior */
		BOUNCE_IN,			/**< Efecto de entrada Bounce genérico */
		LEFT_BOUNCE_IN,		/**< Efecto de entrada Bounce desde la izquierda */
		RIGHT_BOUNCE_IN,	/**< Efecto de entrada Bounce desde la derecha */
		TOP_BOUNCE_IN,		/**< Efecto de entrada Bounce desde la parte superior */
		BOTTOM_BOUNCE_IN,	/**< Efecto de entrada Bounce desde la parte inferior */
		EASE_IN,			/**< Efecto de entrada Ease genérico */
		LEFT_EASE_IN,		/**< Efecto de entrada Ease desde la izquierda */
		RIGHT_EASE_IN,		/**< Efecto de entrada Ease desde la derecha */
		TOP_EASE_IN,		/**< Efecto de entrada Ease desde la parte superior */
		BOTTOM_EASE_IN,		/**< Efecto de entrada Ease desde la parte inferior */
		ELASTIC_IN,			/**< Efecto de entrada Elastic genérico */
		LEFT_ELASTIC_IN,	/**< Efecto de entrada Elastic desde la izquierda */
		RIGHT_ELASTIC_IN,	/**< Efecto de entrada Elastic desde la derecha */
		TOP_ELASTIC_IN,		/**< Efecto de entrada Elastic desde la parte superior */
		BOTTOM_ELASTIC_IN,	/**< Efecto de entrada Elastic desde la parte inferior */
		FADE_IN,			/**< Efecto de entrada Fade */
		HARDROLL_IN,		/**< Efecto de entrada HardRoll */
		POP_IN,				/**< Efecto de entrada Pop */
		ROLL_IN,			/**< Efecto de entrada Roll */
		ROTATE_IN,			/**< Efecto de entrada Rotate */

		// Efectos de salida de escena
		BACK_OUT,			/**< Efecto de salida Back genérico */
		LEFT_BACK_OUT,		/**< Efecto de salida Back hacia la izquierda */
		RIGHT_BACK_OUT,		/**< El efecto salida Back hacia la derecha */
		TOP_BACK_OUT,		/**< El efecto salida Back hacia la parte superior */
		BOTTOM_BACK_OUT,	/**< El efecto salida Back hacia la parte inferior */
		FADE_OUT,			/**< El efecto salida Fade */

		// Efectos de posición en escena
		EASE,				/**< Efecto de posición Ease */
		EASE_X,				/**< Efecto de posición Ease sobre el eje X*/
		EASE_Y,				/**< Efecto de posición Ease sobre el eje Y */
		FADE				/**< Efecto de posición Fade */
	};

	/**
	 * Crea un efecto dado su tipo y parámetros
	 * @param type Tipo de efecto a crear
	 * @param delay Retardo inicial del efecto
	 * @param duration Duración del efecto
	 * @return Nuevo efecto creado
	 * @note El usuario debe encargarse de liberar la memoria ocupada por el
	 * efecto devuelto por el método.
	 */
	static Effect* create(const Type type, const float delay, const float duration);

};

} // namespace bmonkey

#endif //_EFFECT_FACTORY_HPP_
