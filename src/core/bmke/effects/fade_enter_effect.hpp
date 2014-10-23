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

#ifndef _FADE_ENTER_EFFECT_HPP_
#define _FADE_ENTER_EFFECT_HPP_

#include <SFML/Graphics.hpp>
#include "../../../defines.hpp"
#include "../effect.hpp"
#include "../../../thirdparty/DBTweener/dbtweener.h"

namespace bmonkey{

/**
 * Efecto fade de entrada en escena
 *
 * Realiza un efecto fade de entrada en escena mediante la modificación de la
 * opacidad, usando para ello la ecuación del efecto Quad de Robert Penner.
 * El efecto es de posición y no se puede configurar con otra posición de
 * entrada.
 */
class FadeEnterEffect : public Effect
{
public:
	/**
	 * Constructor de la clase
	 */
	FadeEnterEffect(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~FadeEnterEffect(void);

	/**
	 * Inicializa el efecto asignando sus parámetros de procesado
	 * @param win_size Tamaño de la ventana de referencia sobre la que se ejecuta el efecto
	 * @param entity Entidad sobre la que actuará el efecto
	 * @param delay Retraso en segundos antes de comenzar el procesado
	 * @param duration Duración del efecto en segundos
	 * @param from Posición desde donde comienza el efecto
	 */
	virtual void init(const sf::Vector2u& win_size, Entity* entity, const float delay, const float duration, const StartFrom from);

	/**
	 * Actualiza el estado del efecto
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time);

	/**
	 * Reinicia el efecto para comenzar de nuevo su procesado
	 */
	virtual void reset(void);

private:
	CDBTweener::CTween* m_tween;		/**< Tweener usado para el efecto */
	float m_pos;						/**< Posición actual del efecto */
};

} // namespace bmonkey

#endif // _FADE_ENTER_EFFECT_HPP_
