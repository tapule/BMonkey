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

#ifndef _ANIMATION_INL_
#define _ANIMATION_INL_

inline bool Animation::isFinished(void) const
{
	return m_finished;
}

inline float Animation::getDelay(void) const
{
	return m_delay;
}

inline void Animation::setDelay(const float delay)
{
	m_delay = delay;
}

inline float Animation::getDuration(void) const
{
	return m_duration;
}

inline void Animation::setDuration(const float duration)
{
	m_duration = duration;
}

inline sf::Shader* Animation::getShader(void) const
{
	return m_shader;
}

#endif // _ANIMATION_INL_
