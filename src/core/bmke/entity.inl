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

#ifndef _ENTITY_INL_
#define _ENTITY_INL_

#ifdef BMONKEY_DESIGNER
inline bool Entity::isSelected(void) const
{
	return m_selected;
}

inline void Entity::setSelected(const bool selected)
{
	m_selected = selected;
}
#endif

inline Entity::Status Entity::getStatus(void) const
{
	return m_status;
}

inline const Vector2b& Entity::getFlip(void) const
{
	return m_flip;
}

inline void Entity::setFlip(const Vector2b& flip)
{
	m_flip = flip;
}

inline const sf::Color& Entity::getColor(void)
{
	return m_color;
}

inline void Entity::setColor(const sf::Color& color)
{
	m_color = color;
	m_current_color = color;
}

inline unsigned char Entity::getOpacity(void) const
{
	return m_color.a;
}

inline void Entity::setOpacity(const unsigned char opacity)
{
	m_color.a = opacity;
}

inline void Entity::setParent(Entity* entity)
{
	m_parent = entity;
}

inline void Entity::addChild(Entity* entity)
{
	assert(entity);

	m_children.push_back(entity);
}

void Entity::run(void)
{
	m_status = STARTED;
}

#ifdef BMONKEY_DESIGNER
void Entity::stop(void)
{
	m_status = STOPPED;
}
#endif

#endif // _ENTITY_INL_
