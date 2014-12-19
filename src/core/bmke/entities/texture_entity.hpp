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

#ifndef _TEXTURE_ENTITY_HPP_
#define _TEXTURE_ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "../../../defines.hpp"
#include "../entity.hpp"

namespace bmonkey{

/**
 * Entidad con Textura
 *
 * Se trata de una entidad básica a la que se le puede asignar una textura para
 * formar el elemento que será dibujado en el frontend.
 *
 * No se encarga de gestionar la textura, solamente la consume a modo de recurso
 * para presentar una imagen.
 */
class TextureEntity : public Entity
{
public:
	/**
	 * Constructor de la clase
	 */
	TextureEntity(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~TextureEntity(void);

	/**
	 * Establece la anchura y altura de la entidad
	 * @param width Nuevo ancho para la entidad
	 * @param height Nuevo alto para la entidad
	 */
	virtual void setSize(const float width, const float height);

	/**
	 * Establece el color (tinte y opacidad) de la entidad
	 * @param color Nuevos valores para el tiente y la opacidad
	 */
	virtual void setColor(const sf::Color& color);

	/**
	 * Establece la textura que dibujará la entidad
	 * @param texture Textura para dibujar
	 * @note Al cambiar la textura, las dimensiones de la entidad se adaptan
	 * a ella
	 */
	void setTexture (sf::Texture *texture);

private:
	/**
	 * Realiza el dibujado real de esta entidad
	 * @param target Target donde se dibujará la entidad
	 * @param states States para dibujar la entidad
	 */
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * Realiza la actualización real de la entidad
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	virtual void updateCurrent(sf::Time delta_time);

	sf::Texture* m_texture;
	sf::Sprite m_sprite;
};

} // namespace bmonkey

#endif // _TEXTURE_ENTITY_HPP_
