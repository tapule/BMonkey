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

#include "box_entity.hpp"
#include <cassert>

namespace bmonkey{

BoxEntity::BoxEntity(void):
	Entity(),
	m_size(sf::Vector2i(0, 0))
{
	m_box.setOutlineThickness(0);
	m_box.setFillColor(getColor());
	m_box.setSize(sf::Vector2f(m_size));
}

BoxEntity::~BoxEntity(void)
{
}

void BoxEntity::setPivot(Pivot pivot)
{
	sf::FloatRect bounds;
	sf::Vector2i origin;

	m_pivot = pivot;
	bounds = m_box.getLocalBounds();
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
		origin.y =  0;
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

void BoxEntity::setColor(const sf::Color& color)
{
	Entity::setColor(color);
	m_box.setFillColor(color);
}

sf::Vector2i BoxEntity::getSize(void) const
{
	return m_size;
}

void BoxEntity::setSize(const int width, const int height)
{
	m_size.x = width < 0 ? 0 : width;
	m_size.y = height < 0 ? 0 : height;
	m_box.setSize(sf::Vector2f(m_size));
	// Forzamos el cálculo del pivote
	setPivot(m_pivot);
}

void BoxEntity::setSize(const sf::Vector2i& size)
{
	setSize(size.x, size.y);
}

void BoxEntity::updateCurrent(sf::Time delta_time, const sf::Color& color)
{
	m_box.setFillColor(getColor());
}

void BoxEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_box, states);
}

} // namespace bmonkey
