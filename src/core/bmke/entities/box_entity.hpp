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

#ifndef _BOX_ENTITY_HPP_
#define _BOX_ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "../../../defines.hpp"
#include "../entity.hpp"

namespace bmonkey{

/**
 * Entidad para dibujar rectángulos
 *
 * Se trata de una entidad que se puede usar para disponer de rectángulos con
 * color que puedan ser animados igual que el resto de entidades.
 */
class BoxEntity : public Entity
{
public:
	/**
	 * Constructor de la clase
	 */
	BoxEntity(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~BoxEntity(void);

	/**
	 * Establece la posición del pivote de la entidad
	 * @param pivot Nueva posición para el pivote de la entidad
	 */
	virtual void setPivot(Pivot pivot);

	/**
	 * Establece el color (tinte y opacidad) de la entidad
	 * @param color Nuevos valores para el tiente y la opacidad
	 */
	virtual void setColor(const sf::Color& color);

	/**
	 * Obtiene las dimensiones originales de la entidad
	 * @return Dimensiones de la entidad
	 */
	virtual sf::Vector2i getSize(void) const;

	/**
	 * Establece las dimensiones de la entidad
	 * @param width Nuevo ancho para la entidad
	 * @param height Nuevo alto para la entidad
	 */
	virtual void setSize(const int width, const int height);

	/**
	 * Establece las dimensiones de la entidad
	 * @param size Nuevas dimensiones para la entidad
	 */
	void setSize(const sf::Vector2i& size);

protected:
	/**
	 * Realiza la actualización real de la entidad
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 * @param color Color de referencia para actualizar la entidad
	 */
	virtual void updateCurrent(sf::Time delta_time, const sf::Color& color);

	/**
	 * Realiza el dibujado real de esta entidad
	 * @param target Target donde se dibujará la entidad
	 * @param states States para dibujar la entidad
	 * @param color Color a aplicar en el proceso de dibujado
	 */
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Vector2i m_size;		/**< Dimensiones de la entidad */
	sf::RectangleShape m_box;	/**< Primitiva rectángulo para la entidad */
};

} // namespace bmonkey

#endif // _BOX_ENTITY_HPP_
