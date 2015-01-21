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
	m_size(sf::Vector2f(0.f, 0.f))
{
	m_box.setOutlineThickness(0.f);
	m_box.setFillColor(getColor());
	m_box.setSize(m_size);
}

BoxEntity::~BoxEntity(void)
{
}

void BoxEntity::setPivot(Pivot pivot)
{
	sf::FloatRect bounds;
	sf::Vector2f origin;

	m_pivot = pivot;
	bounds = m_box.getLocalBounds();
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

void BoxEntity::setColor(const sf::Color& color)
{
	Entity::setColor(color);
	m_box.setFillColor(color);
}

sf::Vector2f BoxEntity::getSize(void) const
{
	return m_size;
}

void BoxEntity::setSize(const float width, const float height)
{
	m_size.x = width < 0.f ? 0.f : width;
	m_size.y = height < 0.f ? 0.f : height;
	m_box.setSize(m_size);
	// Forzamos el cálculo del pivote
	setPivot(m_pivot);
}

void BoxEntity::setSize(const sf::Vector2f& size)
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
