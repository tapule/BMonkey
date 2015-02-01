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

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <glibmm/ustring.h>
#include "../../defines.hpp"
#include "animation.hpp"

namespace bmonkey{

// Definición de un vector de dos posiciones booleanas
typedef sf::Vector2<bool> Vector2b;

/**
 * Entidad base para los elementos del frontend
 *
 * Las entidades son los elementos fundamentales del frontend, son cada uno de
 * los objetos que se podrán mostrar en pantalla.
 * Una entidad puede estar formada por varias entidades, es decir, actuar como
 * un contenedor de entidades, teniendo sus hijos propiedades que serán
 * relativas al padre.
 * Tienen un estado que determina en que fase de ejecución se encuentran:
 * - Stopped: Se encuentra en su estado inicial, no ha comenzado su ejecución.
 * - Started: Ha comenzado su ejecución.
 * Las entidades pueden tener dos animaciones que actuan sobre ellas y que se
 * ejecutan secuencialmente en orden:
 * - Start: Animación que se ejecuta para posicionar la entidad en su lugar
 * - Position: Animación que se ejecuta mientras que la entidad esté en su lugar
 */
class Entity : public sf::Drawable, public sf::Transformable
{
public:

	// Posibles estados en los que se puede encontrar la entidad
	enum Status
	{
		STOPPED = 0,	/**< Está parada en su estado inicial, no ha comenzado su ejecución */
		STARTED			/**< Ha comenzado su ejecución */
	};

	// Posibles posiciones de origen para el pivote de la entidad
	enum Pivot
	{
		CENTER = 0,		/**< El pivote está centrado en la entidad */
		TOP_LEFT,		/**< El pivote está en la esquina superior izquierda */
		TOP,			/**< El pivote está centrado arriba */
		TOP_RIGHT,		/**< El pivote está en la esquina superior derecha */
		LEFT,			/**< El pivote está centrado a la izquierda */
		RIGHT,			/**< El pivote está centrado a la derecha */
		BOTTOM_LEFT,	/**< El pivote está en la esquina inferior izquierda */
		BOTTOM,			/**< El pivote está centrado abajo */
		BOTTOM_RIGHT	/**< El pivote está en la esquina inferior derecha */
	};

	// Posibles tipos de animaciones que tiene la entidad
	enum AnimationType
	{
		START_ANIMATION = 0,
		POSITION_ANIMATION
	};

	/**
	 * Constructor de la clase
	 */
	Entity(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~Entity(void);

	/**
	 * Obtiene el nombre de la entidad
	 * @return Nombre de la entidad
	 */
	Glib::ustring getName(void) const;

	/**
	 * Establece el nombre de la entidad
	 * @param name Nuevo nombre para la entidad
	 */
	void setName(const Glib::ustring& name);

	/**
	 * Indica si la entidad está habilitada y por lo tanto visible y funcional
	 * @return true si la entidad está habilitada, false en otro caso
	 */
	bool isEnabled(void) const;

	/**
	 * Habilita o deshabilita la entidad
	 * @param enabled Nuevo valor para el estado
	 */
	void setEnabled(const bool enabled);

	/**
	 * Obtiene el estado actual de la entidad
	 * @return Estado de la entidad
	 */
	Status getStatus(void) const;

	/**
	 * Obtiene la posición del pivote de la entidad
	 * @return Posición del pivote de la entidad
	 */
	Pivot getPivot(void) const;

	/**
	 * Establece la posición del pivote de la entidad
	 * @param pivot Nueva posición para el pivote de la entidad
	 */
	virtual void setPivot(Pivot pivot) = 0;

	/**
	 * Obtiene el color de tinte y opacidad de la entidad
	 * @return Color con el tinte y opacidad de la entidad
	 */
	const sf::Color& getColor(void);

	/**
	 * Establece el color de tinte y opacidad de la entidad
	 * @param color Nuevos valores para el tiente y opacidad
	 */
	virtual void setColor(const sf::Color& color);

	/**
	 * Obtiene la opacidad definida en la entidad
	 * @return Opacidad actual de la entidad
	 */
	unsigned char getOpacity(void) const;

	/**
	 * Establece la opacidad de la entidad
	 * @param opacity Nueva opacidad para la entidad
	 */
	void setOpacity(const unsigned char opacity);

	/**
	 * Obtiene la animación que la entidad tiene configurada para un tipo determinado
	 * @param type Tipo de animación requerido
	 * @return Animación configurada en la entidad para el tipo dado
	 */
	Animation* getAnimation(AnimationType type);

	/**
	 * Establece una animación de la entidad para un tipo determinado
	 * @param type Tipo al que asociar la animación
	 * @param animation Animación a asociar
	 */
	void setAnimation(AnimationType type, Animation* animation);

	/**
	 * Obtiene las dimensiones originales de la entidad
	 * @return Dimensiones de la entidad
	 */
	virtual sf::Vector2i getSize(void) const = 0;

	/**
	 * Obtiene la entidad padre
	 * @return Entidad padre o null si no es una entidad padre
	 */
	Entity* getParent(void);

	/**
	 * Establece la entidad padre
	 * @param entity Nueva entidad padre
	 */
	void setParent(Entity* entity);

	/**
	 * Añade una nueva entidad hija a la actual
	 * @param entity Nuevo entidad hija
	 * @note La entidad se convierte en responsable de su nuevo hijo y lo liberará
	 * cuando estime oportuno
	 */
	void addChild(Entity* entity);

	/**
	 * Elimina una entidad hija determinada
	 * @param entity Entidad hija a eliminar
	 */
	void removeChild(Entity* entity);

	/**
	 * Obtiene una referencia al vector interno de entidades hijas
	 * @return Referencia al vector interno de entidades hijas
	 */
	std::vector<Entity* >& getChildren(void);

	/**
	 * Actualiza el estado de la entidad
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	void update(sf::Time delta_time);

	/**
	 * Comienza la ejecución de la entidad desde su punto inicial
	 */
	virtual void run(void);

	/**
	 * Detiene la ejecución de la entidad
	 */
	virtual void stop(void);

protected:
	/**
	 * Actualiza el estado de la entidad incluyendo un color de referencia
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 * @param color Color de referencia para actualizar la entidad
	 */
	void update(sf::Time delta_time, const sf::Color& color);

	/**
	 * Realiza la actualización real de la entidad
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 * @param color Color de referencia para actualizar la entidad
	 */
	virtual void updateCurrent(sf::Time delta_time, const sf::Color& color) = 0;

	/**
	 * Actualiza las entidades hijas de la actual
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 * @param color Color de referencia para actualizar las entidades
	 */
	void updateChildren(sf::Time delta_time, const sf::Color& color);

	/**
	 * Implementación de drawable
	 * @param target Target donde se dibujará la entidad
	 * @param states States para dibujar la entidad
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * Realiza el dibujado real de esta entidad
	 * @param target Target donde se dibujará la entidad
	 * @param states States para dibujar la entidad
	 * @param color Color a aplicar en el proceso de dibujado
	 */
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	Glib::ustring m_name;			/**< Nombre de esta entidad */
	bool m_enabled;					/**< Indica si la entidad está habilitada */
	Status m_status;				/**< Estado en el que se encuentra */
	Pivot m_pivot;					/**< Posición del pivote de la entidad */
	sf::Color m_color;				/**< Tinte y opacidad de la entidad */
	Animation* m_start_animation;	/**< Animación de entrada a la escena */
	Animation* m_position_animation;/**< Animación de posición en la escena */
	Animation* m_current_animation;	/**< Efecto en ejecución */
	Entity* m_parent;				/**< Padre de la entidad en una cadena */
	std::vector<Entity* > m_children; /**< Hijos de la entidad */
};

// Inclusión de los métodos inline
#include "entity.inl"

} // namespace bmonkey

#endif // _ENTITY_HPP_
