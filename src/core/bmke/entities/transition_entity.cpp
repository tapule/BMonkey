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

#include "transition_entity.hpp"
#include <cassert>

namespace bmonkey{

TransitionEntity::TransitionEntity(void):
	Entity(),
	m_texture(nullptr)
{
}

TransitionEntity::~TransitionEntity(void)
{
}

void TransitionEntity::setPivot(Pivot pivot)
{
	sf::FloatRect bounds;
	sf::Vector2i origin;

	m_pivot = pivot;
	bounds = m_sprite.getLocalBounds();
	switch (m_pivot)
	{
	case CENTER:
		origin.x = bounds.width / 2;
		origin.y = bounds.height / 2;
		break;
	case TOP_LEFT:
		origin.x = 0;
		origin.y = 0;
		break;
	case TOP:
		origin.x = bounds.width / 2;
		origin.y = 0;
		break;
	case TOP_RIGHT:
		origin.x = bounds.width;
		origin.y = 0;
		break;
	case LEFT:
		origin.x = 0;
		origin.y = bounds.height / 2;
		break;
	case RIGHT:
		origin.x = bounds.width;
		origin.y = bounds.height / 2;
		break;
	case BOTTOM_LEFT:
		origin.x = 0;
		origin.y = bounds.height;
		break;
	case BOTTOM:
		origin.x = bounds.width / 2;
		origin.y = bounds.height;
		break;
	case BOTTOM_RIGHT:
		origin.x = bounds.width;
		origin.y = bounds.height;
		break;
	}
	setOrigin(origin.x, origin.y);
}

void TransitionEntity::setColor(const sf::Color& color)
{
	Entity::setColor(color);
	m_sprite.setColor(color);
}

sf::Vector2i TransitionEntity::getSize(void) const
{
	sf::FloatRect bounds;
	sf::Vector2i size;

	bounds = m_sprite.getLocalBounds();
	size.x = bounds.width;
	size.y = bounds.height;

	return size;
}

void TransitionEntity::setTexture(sf::Texture *texture)
{
	m_texture = texture;
	m_sprite.setTexture(*m_texture, true);
	// Forzamos el cálculo del pivote
	setPivot(m_pivot);
}

void TransitionEntity::updateCurrent(sf::Time delta_time, const sf::Color& color)
{
	m_sprite.setColor(getColor());
}

void TransitionEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

} // namespace bmonkey
