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

#include "in_effect.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

InEffect::InEffect(void):
	Effect(),
	m_in_from(LEFT)
{
}

InEffect::~InEffect(void)
{
}

void InEffect::init(Entity* entity, const float delay, const float duration)
{
	assert(entity);
	sf::Vector2f position;

	Effect::init(entity, delay, duration);

	// Establecemos la posición del efecto dependiendo del modo de entrada
	switch (m_in_from)
	{
	case LEFT:
		position.x = -1.f * ((entity->getWidth() / 2) + entity->getPosition().x);
		break;
	case RIGHT:
		position.x = m_win_size.x - entity->getPosition().x + (entity->getWidth() / 2);
		break;
	case TOP:
		position.y = -1.f * ((entity->getHeight() / 2) + entity->getPosition().y);
		break;
	case BOTTOM:
		position.y = m_win_size.y - entity->getPosition().y + (entity->getHeight() / 2);
		break;
	}
	setPosition(position);
	m_finished = false;
}

void InEffect::setWindowSize(const sf::Vector2u& win_size)
{
	m_win_size = win_size;
}

void InEffect::setInFrom(const InFrom from)
{
	m_in_from = from;
}

} // namespace bmonkey
