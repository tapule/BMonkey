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

#include "effect.hpp"
#include "entity.hpp"
#include <cassert>

namespace bmonkey{

Effect::Effect(void):
	m_window(nullptr),
	m_entity(nullptr),
	m_delay(0.f),
	m_duration(0.f),
	m_start_from(POSITION),
	m_finished(true),
	m_shader(nullptr),
	m_opacity(255)
{
}

Effect::~Effect(void)
{
	if (m_shader)
	{
		delete m_shader;
	}
}

void Effect::init(sf::Window& window, Entity* entity, const float delay, const float duration, const StartFrom from)
{
	assert(entity);
	sf::Vector2f position;

	m_window = &window;
	m_entity = entity;
	m_delay = delay;
	m_duration = duration;
	m_start_from = from;
	m_opacity = entity->getOpacity();

	// Establecemos la posición del efecto dependiendo del modo de entrada
	switch (from)
	{
	case LEFT:
		position.x = -1.f * ((entity->getWidth() / 2) + entity->getPosition().x);
		break;
	case RIGHT:
		position.x = window.getSize().x - entity->getPosition().x + (entity->getWidth() / 2);
		break;
	case TOP:
		position.y = -1.f * ((entity->getHeight() / 2) + entity->getPosition().y);
		break;
	case BOTTOM:
		position.y = window.getSize().y - entity->getPosition().y + (entity->getHeight() / 2);
		break;
	case POSITION:
		break;
	}
	setPosition(position);
	m_finished = false;
	m_clock.restart();
}

void Effect::reset(void)
{
	init(*m_window, m_entity, m_delay, m_duration, m_start_from);
}

} // namespace bmonkey
