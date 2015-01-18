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

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include "../../defines.hpp"

namespace bmonkey{

class Entity;

/**
 * Animación base para aplicar a las entidades.
 *
 * Las animaciones son objetos que aplican una serie de cambios sobre los
 * valores iniciales de las entidades para conseguir una transformación sobre
 * estas.
 * Las animaciones pueden ser finitas o infinitas. Se puede consultar su estado
 * mediante isFinished(), que indicará si la animación ha terminado o no.
 * Cada animación es responsable de preservar el valor inicial de la entidad
 * sobre la que actua, de forma que se puede restituir una vez finalizado.
 */
class Animation
{
public:
	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial de la animación
	 * @param duration Duración de la animación
	 */
	Animation(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~Animation(void);

	/**
	 * Indica si la animación ha terminado su procesamiento
	 * @return true si se finalizó la animación, false en otro caso
	 */
	bool isFinished(void) const;

	/**
	 * Obtiene el retardo inicial que aplica la animación
	 * @return Retardo inicial
	 */
	float getDelay(void) const;

	/**
	 * Establece el retardo inicial que aplica la animación
	 * @param delay Nuevo retardo para el efecto
	 */
	void setDelay(const float delay);

	/**
	 * Obtiene la duración de la animación
	 * @return Duración de la animación en segundos
	 */
	float getDuration(void) const;

	/**
	 * Establece la duración de la animación
	 * @param duration Duración de la animación en segundos
	 */
	void setDuration(const float duration);

	/**
	 * Obtiene el shader, si lo hay, a aplicar por la animación
	 * @return Shader preconfigurado por la animación o nullptr si no hay shader
	 */
	sf::Shader* getShader(void) const;

	/**
	 * Inicializa la animación para una entidad determinada
	 * @param entity Entidad sobre la que actuará la animación
	 */
	virtual void init(Entity* entity);

	/**
	 * Comienza el procesado de la animación desde su inicio
	 */
	virtual void run(void) = 0;

	/**
	 * Detiene el procesado de la animación dejando la entidad en su estado inicial
	 */
	virtual void stop(void) = 0;

	/**
	 * Actualiza el estado de la animación
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time) = 0;

protected:
	bool m_finished;		/**< Indica si la animación ha terminado */
	Entity* m_entity;		/**< Entidad sobre la que actua la animación */

private:
	float m_delay;			/**< Delay en segundos antes de comenzar */
	float m_duration;		/**< Duración de la animación en segundos */
	sf::Shader* m_shader;	/**< Shader configurado por la animación */
};

// Inclusión de los métodos inline
#include "animation.inl"

} // namespace bmonkey

#endif // _ANIMATION_HPP_
