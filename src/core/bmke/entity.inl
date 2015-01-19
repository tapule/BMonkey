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

inline Glib::ustring Entity::getName(void) const
{
	return m_name;
}

inline void Entity::setName(const Glib::ustring& name)
{
	m_name = name;
}

inline bool Entity::isEnabled(void) const
{
	return m_enabled;
}

inline void Entity::setEnabled(const bool enabled)
{
	m_enabled = enabled;
}

inline Entity::Status Entity::getStatus(void) const
{
	return m_status;
}

inline Entity::Pivot Entity::getPivot(void) const
{
	return m_pivot;
}

inline const sf::Color& Entity::getColor(void)
{
	return m_color;
}

inline void Entity::setColor(const sf::Color& color)
{
	m_color = color;
}

inline unsigned char Entity::getOpacity(void) const
{
	return m_color.a;
}

inline void Entity::setOpacity(const unsigned char opacity)
{
	m_color.a = opacity;
	setColor(m_color);
}

inline Entity* Entity::getParent(void)
{
	return m_parent;
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

inline std::vector<Entity* >& Entity::getChildren(void)
{
	return m_children;
}

inline void Entity::update(sf::Time delta_time)
{
	update(delta_time, m_color);
}

#endif // _ENTITY_INL_
