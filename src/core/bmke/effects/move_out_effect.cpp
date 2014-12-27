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

#include "move_out_effect.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

MoveOutEffect::MoveOutEffect(void):
	Effect(),
	m_destination(LEFT),
	m_final_pos(0)
{
}

MoveOutEffect::~MoveOutEffect(void)
{
}

void MoveOutEffect::init(Entity* entity, const float delay, const float duration)
{
	assert(entity);
	sf::Vector2f position;
	sf::Vector2f size;

	Effect::init(entity, delay, duration);

	size = entity->getSize();

	// Establecemos la posición final del efecto dependiendo del modo de salida
	switch (m_destination)
	{
	case LEFT:
		m_final_pos = -1.f * ((size.x / 2.f) + entity->getPosition().x);
		break;
	case RIGHT:
		m_final_pos = m_win_size.x - entity->getPosition().x + (size.x / 2.f);
		break;
	case TOP:
		m_final_pos = -1.f * ((size.y / 2.f) + entity->getPosition().y);
		break;
	case BOTTOM:
		m_final_pos = m_win_size.y - entity->getPosition().y + (size.y / 2.f);
		break;
	}
}

} // namespace bmonkey
