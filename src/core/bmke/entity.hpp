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

#define BMONKEY_DESIGNER


#include <SFML/Graphics.hpp>
#include <vector>
#include "../../defines.hpp"
#include "effect.hpp"

namespace bmonkey{

/**
 * Entidad base para los elementos del frontend
 *
 * Las entidades son los elementos fundamentales del frontend, son cada uno de
 * los objetos que se pueden dibujar en pantalla.
 * Una entidad puede estar formada por varias entidades, teniendo sus hijos
 * propiedades relativas al padre.
 * Tienen un estado determina en que fase de ejecución se encuentran:
 * - Stopped: Se encuentra en su estado inicial, no ha comenzado su ejecución.
 * - Started: Ha comenzado su ejecución y está entrando en la escena.
 * - Placed: Se encuentra en ejecución y posicionada en su lugar, está en su
 *   bucle principal de ejecución.
 */
class Entity : public sf::Drawable, public sf::Transformable
{
public:

	// Posibles estados en los que se puede encontrar la entidad
	enum Status
	{
		STOPPED = 0,	/**< Está parada en su estado inicial, no ha comenzado su ejecución */
		STARTED,		/**< Ha comenzado su ejecución y está entrando en la escena */
		PLACED			/**< Se encuentra en ejecución y posicionada en su lugar */
	};

	/**
	 * Constructor de la clase
	 */
	Entity(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~Entity(void);

#ifdef BMONKEY_DESIGNER
	/**
	 * Indica si la entidad está visible (habilitada)
	 * @return true si la entidad está visible, false en otro caso
	 */
	bool isEnabled(void) const;

	/**
	 * Activa o desactiva la visibilidad de la entidad
	 * @param enabled Nuevo valor para la visibilidad de la entidad
	 */
	void setEnabled(const bool enabled);

	/**
	 * Indica si la entidad está bloqueada
	 * @return true si la entidad está bloqueada, false en otro caso
	 */
	bool isBlocked(void) const;

	/**
	 * Activa o desactiva el bloqueo de la entidad
	 * @param blocked Nuevo valor para el bloqueo
	 */
	void setBlocked(const bool blocked);

	/**
	 * Indica si la entidad está seleccionada
	 * @return true si la entidad está seleccionada, false en otro caso
	 */
	bool isSelected(void) const;

	/**
	 * Selecciona o deselecciona la entidad
	 * @param selected Nuevo valor para el estado de selección
	 */
	void setSelected(const bool selected);
#endif

	/**
	 * Obtiene el estado actual de la entidad
	 * @return Estado de la entidad
	 */
	Status getStatus(void) const;

	/**
	 * Obtiene la anchura de la entidad
	 * @return Anchura de la entidad
	 */
	float getWidth(void) const;

	/**
	 * Obtiene la altura de la entidad
	 * @return Altura de la entidad
	 */
	float getHeight(void) const;

	/**
	 * Establece la anchura y altura de la entidad
	 * @param width Nuevo ancho para la entidad
	 * @param height Nuevo alto para la entidad
	 */
	virtual void setSize(const float width, const float height);

	/**
	 * Indica si la entidad tiene el espejado horizontal activado
	 * @return true si el espejado horizontal está activado, falso en otro caso
	 */
	bool getFlipX(void) const;

	/**
	 * Indica si la entidad tiene el espejado vertical activado
	 * @return true si el espejado vertical está activado, falso en otro caso
	 */
	bool getFlipY(void) const;

	/**
	 * Establece la anchura y altura de la entidad
	 * @param width Nuevo ancho para la entidad
	 * @param height Nuevo alto para la entidad
	 */
	void setFlip(const bool x, const bool y);

	/**
	 * Obtiene el color (tinte y opacidad) de la entidad
	 * @return Color con el tinte y opacidad de la entidad
	 */
	sf::Color& getColor(void);

	/**
	 * Establece el color (tinte y opacidad) de la entidad
	 * @param color Nuevos valores para el tiente y la opacidad
	 */
	void setColor(const sf::Color& color);

	/**
	 * Obtiene la opacidad actual (en tiempo real) de la entidad
	 * @return Opacidad actual de la entidad
	 */
	unsigned char getOpacity(void);

	/**
	 * Establece el efecto que usará la entidad para entrar en la escena
	 * @param effect Nuevo efecto que se usará para entrar en la escena
	 * @note El efecto debe estar inicializado
	 * @note La entidad se convierte en responsable del efecto y lo liberará
	 * cuando estime oportuno
	 */
	void setStartEffect(Effect* effect);

	/**
	 * Establece el efecto que usará la entidad durante la escena
	 * @param effect Nuevo efecto que se usará durante la escena
	 * @note El efecto debe estar inicializado
	 * @note La entidad se convierte en responsable del efecto y lo liberará
	 * cuando estime oportuno
	 */
	void setPlaceEffect(Effect* effect);

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
	 * Actualiza el estado de la entidad
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	void update(sf::Time delta_time);

	/**
	 * Resetea la entidad devolviendola a su posición, rotación, etc iniciales
	 */
	virtual void reset(void);

private:
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
	 */
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;

#ifdef BMONKEY_DESIGNER
	/**
	 * Dibuja la malla de selección que indica que el elemento está seleccionado
	 * @param target Target donde se dibujará la entidad
	 * @param states States para dibujar la entidad
	 */
	virtual void drawGrid(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * Actualiza el grid de selección de la entidad
	 * @param width Nueva anchura para el grid
	 * @param height Nueva altura para el grid
	 */
	void updateGrid(const float width, const float height);
#endif

	/**
	 * Realiza la actualización real de la entidad
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void updateCurrent(sf::Time delta_time);

	/**
	 * Actualiza las entidades hijas de la actual
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	void updateChildren(sf::Time delta_time);


#ifdef BMONKEY_DESIGNER
	bool m_enabled;				/**< Indica si la entidad está visible */
	bool m_blocked;				/**< Indica si la entidad recibe modificaciones con el ratón */
	bool m_selected;			/**< Indica si la entidad está seleccionada */
	sf::RectangleShape m_grid_box;	/**< Rectángulo que hace de grid para selección */
	sf::RectangleShape m_grid_dot;	/**< Marcador del origen en el grid */
#endif

	Status m_status;			/**< Estado en el que se encuentra */
	float m_width;				/**< Anchura de la entidad */
	float m_height;				/**< Altura de la entidad */
	bool m_flipx;				/**< Indica si se hace el flip en x */
	bool m_flipy;				/**< Indica si se hace el flip en y */
	sf::Color m_color;			/**< Tinte y opacidad de la entidad */
	Effect* m_start_effect;		/**< Efecto de entrada a la escena */
	Effect* m_place_effect;		/**< Efecto de posición en la escena */
	Effect* m_current_effect;	/**< Efecto en ejecución */

	Entity* m_parent;			/**< Padre de la entidad en una cadena */
	std::vector<Entity* > m_children; /**< Hijos de la entidad */
};

// Inclusión de los métodos inline
#include "entity.inl"

} // namespace bmonkey

#endif // _ENTITY_HPP_
