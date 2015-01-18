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

#ifndef _EASE_ANIMATION_HPP_
#define _EASE_ANIMATION_HPP_

#include "../animation.hpp"
#include "../../../thirdparty/DBTweener/dbtweener.h"

namespace bmonkey{

/**
 * Animación ease
 *
 * Realiza una animación de movimiento contínuo horizontal o vertical con un
 * desplazamiento respecto al origen del elemento.
 */
class EaseAnimation : public Animation
{
public:

	// Ejes sobre los que aplicar la animación
	enum Axis
	{
		X,	/**< La animación se aplica sobre el eje X */
		Y	/**< La animación se aplica sobre el eje Y */
	};

	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial de la animación
	 * @param duration Duración de la animación
	 */
	EaseAnimation(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~EaseAnimation(void);

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

	/**
	 * Establece el eje sobre el que se aplica la animación
	 * @param axis Nuevo eje sobre el que aplicar la animación
	 */
	void setAxis(const Axis axis);

private:
	sf::Clock m_clock;				/**< Reloj para controlar el tiempo transcurrido */
	CDBTweener::CTween* m_tween;	/**< Tweener usado para la animación */
	Axis m_axis;					/**< Eje sobre el que se aplica la animación */
	float m_current_pos;			/**< Posición actual de la animación */
	float m_dest_pos_a;				/**< Primer punto de destino de la aniamción */
	float m_dest_pos_b;				/**< Segundo punto de destino de la animación */
	sf::Vector2f m_entity_pos;		/**< Posición inicial de la entidad */
};

} // namespace bmonkey

#endif // _EASE_ANIMATION_HPP_
