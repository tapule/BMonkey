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

#ifndef _FADE_OUT_ANIMATION_HPP_
#define _FADE_OUT_ANIMATION_HPP_

#include "../animation.hpp"
#include "../../../thirdparty/DBTweener/dbtweener.h"

namespace bmonkey{

/**
 * Animación fade de salida de escena
 *
 * Realiza una animación fade de salida de escena mediante la modificación de la
 * opacidad de la entidad, usando para ello la ecuación del efecto Quad de
 * Robert Penner.
 */
class FadeOutAnimation : public Animation
{
public:
	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial de la animación
	 * @param duration Duración de la animación
	 */
	FadeOutAnimation(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~FadeOutAnimation(void);

	/**
	 * Inicializa la animación para una entidad determinada
	 * @param entity Entidad sobre la que actuará la animación
	 */
	virtual void init(Entity* entity);

	/**
	 * Comienza el procesado de la animación desde su inicio
	 */
	virtual void run(void);

	/**
	 * Detiene el procesado de la animación dejando la entidad en su estado inicial
	 */
	virtual void stop(void);

	/**
	 * Actualiza el estado de la animación
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time);

private:
	sf::Clock m_clock;				/**< Reloj para controlar el tiempo transcurrido */
	CDBTweener::CTween* m_tween;	/**< Tweener usado para la animación */
	float m_current_pos;			/**< Posición actual de la animación */
	sf::Color m_entity_color;		/**< Color original de la entidad */
};

} // namespace bmonkey

#endif // _FADE_OUT_ANIMATION_HPP_
