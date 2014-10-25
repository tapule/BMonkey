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

#include "texture_entity.hpp"
#include <cassert>

namespace bmonkey{

TextureEntity::TextureEntity(void):
	Entity(),
	m_texture(nullptr)
{
}

TextureEntity::~TextureEntity(void)
{
}

void TextureEntity::setSize(const float width, const float height)
{
	sf::Vector2u texture_size;

	Entity::setSize(width, height);

	if (m_texture)
	{
		texture_size = m_texture->getSize();
		setScale(width/texture_size.x, height/texture_size.y);
	}
}

void TextureEntity::setColor(const sf::Color& color)
{
	Entity::setColor(color);
	m_sprite.setColor(getColor());
}

void TextureEntity::setTexture (sf::Texture *texture)
{
	sf::Vector2u texture_size;
	sf::FloatRect bounds;

	m_texture = texture;
	m_sprite.setTexture(*m_texture, true);
	// Movemos el origen al centro del sprite
	bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	if (m_texture)
	{
		texture_size = m_texture->getSize();
		setSize(texture_size.x, texture_size.y);
	}
}

void TextureEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

void TextureEntity::updateCurrent(sf::Time delta_time)
{
	sf::Color color = getColor();

	// Actualizamos el color del sprite
	color.a = getCurrentOpacity();
	m_sprite.setColor(color);
}

} // namespace bmonkey
