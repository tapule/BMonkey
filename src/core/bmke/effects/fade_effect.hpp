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

#ifndef _FADE_EFFECT_HPP_
#define _FADE_EFFECT_HPP_

#include "../effect.hpp"
#include "../../../thirdparty/DBTweener/dbtweener.h"

namespace bmonkey{

/**
 * Efecto fade
 *
 * Realiza un efecto fade contínuo mediante la modificación de la opacidad. En
 * esencia es un fade in seguido de un fade out repetido constantemente. Usa
 * la ecuación lineal
 */
class FadeEffect : public Effect
{
public:
	/**
	 * Constructor de la clase
	 */
	FadeEffect(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~FadeEffect(void);

	/**
	 * Inicializa el efecto asignando sus parámetros de procesado
	 * @param entity Entidad sobre la que actuará el efecto
	 * @param delay Retraso en segundos antes de comenzar el procesado
	 * @param duration Duración del efecto en segundos
	 */
	virtual void init(Entity* entity, const float delay, const float duration);

	/**
	 * Actualiza el estado del efecto
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time);

private:
	CDBTweener::CTween* m_tween;		/**< Tweener usado para el efecto */
	float m_pos;						/**< Posición actual del efecto */
};

} // namespace bmonkey

#endif // _FADE_EFFECT_HPP_
