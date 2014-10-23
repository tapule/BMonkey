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
 * Los efectos son objetos transformables que aplican una serie de cambios sobre
 * los valores iniciales de las entidades para conseguir una transformación
 * sobre estas.
 * Realmente no transforman la entidad directamente, sino que el propio estado
 * del efecto se debe combinar con el estado de la entidad para obtener la
 * transformación aplicada, de este modo los efectos se pueden combinar.
 * Los efectos pueden ser finitos o infinitos. Se puede consultar el estado del
 * efecto mediante isFinished(), que indicará si el efecto ha terminado o no.
 */
class Effect : public sf::Transformable
{
public:

	// Posibles posiciones desde donde puede comenzar el efecto
	enum StartFrom
	{
		LEFT,		/**< El efecto comienza desde la izquierda de la pantalla */
		RIGHT,		/**< El efecto comienza desde la derecha de la pantalla */
		TOP,		/**< El efecto comienza desde la parte superior de la pantalla */
		BOTTOM,		/**< El efecto comienza desde la parte inferior de la pantalla */
		POSITION	/**< El efecto comienza desde la propia posición */
	};

	/**
	 * Constructor de la clase
	 */
	Effect(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~Effect(void);

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

	/**
	 * Indica si el efecto ha terminado su procesamiento
	 * @return true si se finalizó el efecto, false en otro caso
	 */
	bool isFinished(void) const;

	/**
	 * Obtiene la opacidad procesada por el efecto
	 * @return Opacidad obtenida en el procesamiento del efecto
	 */
	unsigned char getOpacity(void) const;

	/**
	 * Obtiene el shader, si lo hay, a aplicar por el efecto
	 * @return Shader preconfigurado por el efecto o nullptr si no hay shader
	 */
	sf::Shader* getShader(void) const;

protected:
	sf::Vector2u m_win_size;/**< Tamaño de la ventana de referencia para los efectos */
	Entity* m_entity;		/**< Entidad sobre la que actua el efecto */
	float m_delay;			/**< Delay en segundos antes de comenzar el efecto */
	sf::Clock m_clock;		/**< Reloj para controlar el tiempo transcurrido */
	float m_duration;		/**< Duración del efecto en segundos */
	StartFrom m_start_from;	/**< Posición desde donde comienza el efecto */
	bool m_finished;		/**< Indica si el efecto ha terminado */
	sf::Shader* m_shader;	/**< Shader configurado por el efecto */
	unsigned char m_opacity;/**< Transparencia procesada por el efecto */
};

// Inclusión de los métodos inline
#include "effect.inl"

} // namespace bmonkey

#endif // _EFFECT_HPP_
