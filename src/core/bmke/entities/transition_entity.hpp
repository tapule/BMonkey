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

#ifndef _TRANSITION_ENTITY_HPP_
#define _TRANSITION_ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "../../../defines.hpp"
#include "../entity.hpp"

namespace bmonkey{

/**
 * Entidad para transiciones
 *
 * Se trata de una entidad usada en las transiciones entre escenas.
 * Básicamente se trata de una entidad a la que se puede asignar una textura
 * que será mostrada en pantalla.
 *
 * No se encarga de gestionar la textura, solamente la consume a modo de recurso
 * para presentar una imagen.
 */
class TransitionEntity : public Entity
{
public:
	/**
	 * Constructor de la clase
	 */
	TransitionEntity(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~TransitionEntity(void);

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
	 * Establece la textura que dibujará la entidad
	 * @param texture Textura para dibujar
	 * @note Al cambiar la textura, las dimensiones de la entidad se adaptan
	 * a ella
	 */
	void setTexture(sf::Texture *texture);

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
	sf::Texture* m_texture;		/**< Textura mostrada por la entidad */
	sf::Sprite m_sprite;		/**< Sprite interno para mostrar la textura */
};

} // namespace bmonkey

#endif // _TRANSITION_ENTITY_HPP_
