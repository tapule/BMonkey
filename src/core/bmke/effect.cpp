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
#include <cassert>

namespace bmonkey{

Effect::Effect(void):
	m_entity(nullptr),
	m_delay(0.f),
	m_speed(0.f),
	m_finished(true),
	m_shader(nullptr),
	m_opacity(0)
{
}

Effect::~Effect(void)
{
	if (m_shader)
	{
		delete m_shader;
	}
}

void Effect::init(const Entity* entity, const float delay, const float speed)
{
	m_entity = entity;
	m_delay = delay;
	m_speed = speed;
}

} // namespace bmonkey
