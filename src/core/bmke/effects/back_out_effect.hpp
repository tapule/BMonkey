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

#ifndef _BACK_OUT_EFFECT_HPP_
#define _BACK_OUT_EFFECT_HPP_

#include "move_out_effect.hpp"
#include "../../../thirdparty/DBTweener/dbtweener.h"

namespace bmonkey{

/**
 * Efecto de salida de escena usando la ecuación Back
 *
 * Realiza un efecto de salida de escena mediante la modificación de la posición
 * usando para ello la ecuación del efecto especial Back
 * El efecto se puede configurar para finalizar en la izquierda, derecha, arriba
 * o abajo de una ventana indicada.
 */
class BackOutEffect : public MoveOutEffect
{
public:
	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial del efecto
	 * @param duration Duración del efecto
	 */
	BackOutEffect(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~BackOutEffect(void);

	/**
	 * Comienza el procesado del efecto desde su comienzo
	 */
	virtual void run(void);

	/**
	 * Actualiza el estado del efecto
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time);

private:
	sf::Clock m_clock;				/**< Reloj para controlar el tiempo transcurrido */
	CDBTweener::CTween* m_tween;	/**< Tweener usado para el efecto */
	float m_current_pos;			/**< Posición actual del efecto */
};

} // namespace bmonkey

#endif // _BACK_OUT_EFFECT_HPP_
