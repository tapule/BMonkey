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

#ifndef _EFFECT_INL_
#define _EFFECT_INL_

inline void Effect::reset(void)
{
	init(m_entity, m_delay, m_duration);
}

inline bool Effect::isFinished(void) const
{
	return m_finished;
}

inline sf::Color Effect::getColor(void) const
{
	return m_color;
}

inline unsigned char Effect::getOpacity(void) const
{
	return m_color.a;
}

inline Entity* Effect::getEntity(void) const
{
	return m_entity;
}

inline float Effect::getDelay(void) const
{
	return m_delay;
}

inline float Effect::getDuration(void) const
{
	return m_duration;
}

inline sf::Shader* Effect::getShader(void) const
{
	return m_shader;
}

#endif // _EFFECT_INL_
