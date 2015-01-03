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

#ifndef _EASE_EFFECT_HPP_
#define _EASE_EFFECT_HPP_

#include "../effect.hpp"
#include "../../../thirdparty/DBTweener/dbtweener.h"

namespace bmonkey{

/**
 * Efecto ease
 *
 * Realiza un efecto de movimiento continuo horizontal o vertical con un
 * desplazamiento respecto al origen del elemento.
 */
class EaseEffect : public Effect
{
public:

	// Ejes sobre los que aplicar el efecto
	enum Axis
	{
		X,	/**< El efecto se aplica sobre el eje X */
		Y	/**< El efecto se aplica sobre el eje Y */
	};

	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial del efecto
	 * @param duration Duración del efecto
	 */
	EaseEffect(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~EaseEffect(void);

	/**
	 * Inicializa el efecto para una entidad determinada
	 * @param entity Entidad sobre la que actuará el efecto
	 */
	virtual void init(Entity* entity);

	/**
	 * Comienza el procesado del efecto desde su comienzo
	 */
	virtual void run(void);

	/**
	 * Detiene el procesado del efecto dejando la entidad en su estado inicial
	 */
	virtual void stop(void);

	/**
	 * Actualiza el estado del efecto
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time);

	/**
	 * Establece el eje sobre el que se aplica el efecto
	 * @param axis Nuevo eje sobre el que aplicar el efecto
	 */
	void setAxis(const Axis axis);

private:
	sf::Clock m_clock;				/**< Reloj para controlar el tiempo transcurrido */
	CDBTweener::CTween* m_tween;	/**< Tweener usado para el efecto */
	Axis m_axis;					/**< Eje sobre el que se aplica el efecto */
	float m_current_pos;			/**< Posición actual del efecto */
	float m_dest_pos_a;				/**< Posición de destino del efecto */
	float m_dest_pos_b;				/**< Posición de destino del efecto */
	sf::Vector2f m_entity_pos;		/**< Posición inicial de la entidad */
};

} // namespace bmonkey

#endif // _EASE_EFFECT_HPP_
