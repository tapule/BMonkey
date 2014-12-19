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
#include "../../defines.hpp"

namespace bmonkey{

// Definición de un vector de dos posiciones booleanas
typedef sf::Vector2<bool> Vector2b;

/**
 * Entidad base para los elementos del frontend
 *
 * Las entidades son los elementos fundamentales del frontend, son cada uno de
 * los objetos que se pueden dibujar en pantalla.
 * Una entidad puede estar formada por varias entidades, teniendo sus hijos
 * propiedades relativas al padre.
 */
class Entity : public sf::Drawable, public sf::Transformable
{
public:

	/**
	 * Constructor de la clase
	 */
	Entity(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~Entity(void);

	/**
	 * Nueva versión de Transformable::setScale para que soporte el grid de
	 * selección
	 * @param factorX Nuevo factor de escala horizontal
	 * @param factorY Nuevo factor de escala vertical
	 */
	void setScale(float factorX, float factorY);

#ifdef BMONKEY_DESIGNER
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
	 * Obtiene el valor del espejado actual de la entidad
	 * @return Valor actuala del espejado
	 */
	const Vector2b& getFlip(void) const;

	/**
	 * Establece el espejado horizontal y vertical de la entidad
	 * @param x Nuevo espejado horizontal para la entidad
	 * @param y Nuevo espejado vertical para la entidad
	 */
	void setFlip(const bool x, const bool y);

	/**
	 * Establece el espejado horizontal y vertical de la entidad
	 * @param flip Nuevo espejado para la entidad
	 */
	void setFlip(const Vector2b& flip);

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
	 * Obtiene la primera entidad hija
	 * @return Primera entidad hija
	 */
	Entity* getFirstChild(void);

	/**
	 * Obtiene la última entidad hija
	 * @return Última entidad hija
	 */
	Entity* getLastChild(void);

	/**
	 * Actualiza el estado de la entidad
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void update(sf::Time delta_time);

	/**
	 * Comienza la ejecución de la entidad desde su punto inicial
	 */
	virtual void run(void);

#ifdef BMONKEY_DESIGNER
	/**
	 * Detiene la ejecución de la entidad, pasando esta a modo edición
	 */
	virtual void stop(void);
#endif

protected:
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
	virtual void updateGrid(const float width, const float height) const = 0;
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
	bool m_selected;				/**< Indica si la entidad está seleccionada */
	sf::RectangleShape m_grid_box;	/**< Rectángulo que hace de grid para selección */
	sf::RectangleShape m_grid_dot;	/**< Marcador del origen en el grid */
#endif

	Vector2b m_flip;			/**< Valores del espejado */
	sf::Color m_color;			/**< Tinte y opacidad de la entidad */

	Entity* m_parent;			/**< Padre de la entidad en una cadena */
	std::vector<Entity* > m_children; /**< Hijos de la entidad */
};

// Inclusión de los métodos inline
#include "entity.inl"

} // namespace bmonkey

#endif // _ENTITY_HPP_
