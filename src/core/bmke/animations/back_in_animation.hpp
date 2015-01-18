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

#ifndef _BACK_IN_ANIMATION_HPP_
#define _BACK_IN_ANIMATION_HPP_

#include "move_in_animation.hpp"
#include "../../../thirdparty/DBTweener/dbtweener.h"

namespace bmonkey{

/**
 * Animación de entrada en escena usando la ecuación Back
 *
 * Realiza una animación de entrada en escena mediante la modificación de la
 * posición de la entidad, usando para ello la ecuación del efecto especial Back
 * de Robert Penner.
 * La animación se puede configurar para comenzar desde la izquierda, derecha,
 * arriba o abajo de una ventana indicada.
 */
class BackInAnimation : public MoveInAnimation
{
public:
	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial de la animación
	 * @param duration Duración de la animación
	 */
	BackInAnimation(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~BackInAnimation(void);

	/**
	 * Comienza el procesado de la animación desde su inicio
	 */
	virtual void run(void);

	/**
	 * Actualiza el estado de la animación
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time);

private:
	sf::Clock m_clock;				/**< Reloj para controlar el tiempo transcurrido */
	CDBTweener::CTween* m_tween;	/**< Tweener usado para la animación */
	float m_current_pos;			/**< Posición actual de la animación */
};

} // namespace bmonkey

#endif // _BACK_IN_ANIMATION_HPP_
