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

#ifndef _MOVE_IN_ANIMATION_INL_
#define _MOVE_IN_ANIMATION_INL_

inline void MoveInAnimation::setWindowSize(const sf::Vector2u& win_size)
{
	m_win_size = win_size;
}

inline sf::Vector2u MoveInAnimation::getWindowSize(void) const
{
	return m_win_size;
}

inline void MoveInAnimation::setOrigin(const Origin origin)
{
	m_origin = origin;
}

inline MoveInAnimation::Origin MoveInAnimation::getOrigin(void) const
{
	return m_origin;
}

#endif // _MOVE_IN_ANIMATION_INL_
