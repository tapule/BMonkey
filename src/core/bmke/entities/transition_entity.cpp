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
	sf::Vector2f origin;

	m_pivot = pivot;
	bounds = m_sprite.getLocalBounds();
	switch (m_pivot)
	{
	case CENTER:
		setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		break;
	case TOP_LEFT:
		setOrigin(0.f, 0.f);
		break;
	case TOP:
		setOrigin(bounds.width / 2.f, 0.f);
		break;
	case TOP_RIGHT:
		setOrigin(bounds.width, 0.f);
		break;
	case LEFT:
		setOrigin(0.f, bounds.height / 2.f);
		break;
	case RIGHT:
		setOrigin(bounds.width, bounds.height / 2.f);
		break;
	case BOTTOM_LEFT:
		setOrigin(0.f, bounds.height);
		break;
	case BOTTOM:
		setOrigin(bounds.width / 2.f, bounds.height);
		break;
	case BOTTOM_RIGHT:
		setOrigin(bounds.width, bounds.height);
		break;
	}
}

void TransitionEntity::setColor(const sf::Color& color)
{
	Entity::setColor(color);
	m_sprite.setColor(color);
}

sf::Vector2f TransitionEntity::getSize(void) const
{
/*	sf::Vector2u texture_size;
	sf::Vector2f size;

	if (m_texture)
	{
		texture_size = m_texture->getSize();
		size = getScale();
		size.x = std::abs(size.x) * texture_size.x;
		size.y = std::abs(size.y) * texture_size.y;
	}
	return size;*/

	sf::Vector2u texture_size;
	sf::Vector2f size;
	sf::FloatRect r;

	if (m_texture)
	{
		texture_size = m_texture->getSize();
		r = sf::FloatRect(0.f, 0.f, texture_size.x, texture_size.y);
		r = getTransform().transformRect(r);

		size.x = r.width;
		size.y = r.height;
	}
	return size;
}

void TransitionEntity::setTexture(sf::Texture *texture)
{
	m_texture = texture;
	m_sprite.setTexture(*m_texture, true);
	// Movemos el origen dependiendo del pivote de la entidad
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
