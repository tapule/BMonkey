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

#include "move_out_animation.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

MoveOutAnimation::MoveOutAnimation(const float delay, const float duration):
	Animation(delay, duration),
	m_destination(LEFT)
{
}

MoveOutAnimation::~MoveOutAnimation(void)
{
	// Forzamos la parada para que restaure las propiedades de la entidad
	stop();
}

void MoveOutAnimation::init(Entity* entity)
{
	sf::Vector2i size;

	Animation::init(entity);

	m_entity_pos = entity->getPosition();
	size = entity->getSize();

	// Establecemos la posición final de la animación dependiendo del modo de salida
	switch (m_destination)
	{
	case LEFT:
		m_dest_pos.x = 0.f - size.x;
		m_dest_pos.y = m_entity_pos.y;
		break;
	case RIGHT:
		m_dest_pos.x = m_entity_pos.x + (m_win_size.x - m_entity_pos.x) + size.x;
		m_dest_pos.y = m_entity_pos.y;
		break;
	case TOP:
		m_dest_pos.x = m_entity_pos.x;
		m_dest_pos.y = 0.f - size.y;
		break;
	case BOTTOM:
		m_dest_pos.x = m_entity_pos.x;
		m_dest_pos.y = m_entity_pos.y + (m_win_size.y - m_entity_pos.y) + size.y;
		break;
	}
}

void MoveOutAnimation::stop(void)
{
	m_finished = true;
	m_entity->setPosition(m_entity_pos);
}

} // namespace bmonkey
