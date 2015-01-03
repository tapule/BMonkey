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

#ifndef _EFFECT_HPP_
#define _EFFECT_HPP_

#include <SFML/Graphics.hpp>
#include "../../defines.hpp"

namespace bmonkey{

class Entity;

/**
 * Efecto base para aplicar animaciones a las entidades.
 *
 * Los efectos son objetos que aplican una serie de cambios sobre los valores
 * iniciales de las entidades para conseguir una transformación sobre estas.
 * Los efectos pueden ser finitos o infinitos. Se puede consultar el estado del
 * efecto mediante isFinished(), que indicará si el efecto ha terminado o no.
 * Cada efecto es responsable de preservar el valor inicial de la entidad sobre
 * la que actua, de forma que se puede restituir una vez finalizado.
 */
class Effect
{
public:
	/**
	 * Constructor de la clase
	 * @param delay Retardo inicial del efecto
	 * @param duration Duración del efecto
	 */
	Effect(const float delay, const float duration);

	/**
	 * Destructor de la clase
	 */
	virtual ~Effect(void);

	/**
	 * Indica si el efecto ha terminado su procesamiento
	 * @return true si se finalizó el efecto, false en otro caso
	 */
	bool isFinished(void) const;

	/**
	 * Obtiene el retardo inicial que aplica el efecto
	 * @return Retardo inicial
	 */
	float getDelay(void) const;

	/**
	 * Establece el retardo inicial que aplica el efecto
	 * @param delay Nuevo retardo para el efecto
	 */
	void setDelay(const float delay);

	/**
	 * Obtiene la duración del efecto
	 * @return Duración del efecto en segundos
	 */
	float getDuration(void) const;

	/**
	 * Establece la duración del efecto
	 * @param duration Duración del efecto en segundos
	 */
	void setDuration(const float duration);

	/**
	 * Obtiene el shader, si lo hay, a aplicar por el efecto
	 * @return Shader preconfigurado por el efecto o nullptr si no hay shader
	 */
	sf::Shader* getShader(void) const;

	/**
	 * Inicializa el efecto para una entidad determinada
	 * @param entity Entidad sobre la que actuará el efecto
	 */
	virtual void init(Entity* entity);

	/**
	 * Comienza el procesado del efecto desde su comienzo
	 */
	virtual void run(void) = 0;

	/**
	 * Detiene el procesado del efecto dejando la entidad en su estado inicial
	 */
	virtual void stop(void) = 0;

	/**
	 * Actualiza el estado del efecto
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time) = 0;

protected:
	bool m_finished;		/**< Indica si el efecto ha terminado */
	Entity* m_entity;		/**< Entidad sobre la que actua el efecto */

private:
	float m_delay;			/**< Delay en segundos antes de comenzar el efecto */
	float m_duration;		/**< Duración del efecto en segundos */
	sf::Shader* m_shader;	/**< Shader configurado por el efecto */
};

// Inclusión de los métodos inline
#include "effect.inl"

} // namespace bmonkey

#endif // _EFFECT_HPP_
