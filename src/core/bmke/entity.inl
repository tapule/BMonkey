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

#ifdef BMONKEY_DESIGNER
inline bool Entity::isEnabled(void) const
{
	return m_enabled;
}

inline void Entity::setEnabled(const bool enabled)
{
	m_enabled = enabled;
}

inline bool Entity::isBlocked(void) const
{
	return m_blocked;
}

inline void Entity::setBlocked(const bool blocked)
{
	m_blocked = blocked;
}

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

inline float Entity::getWidth(void) const
{
	return m_width;
}

inline float Entity::getHeight(void) const
{
	return m_height;
}

inline bool Entity::getFlipX(void) const
{
	return m_flipx;
}

inline bool Entity::getFlipY(void) const
{
	return m_flipy;
}

inline void Entity::setFlip(const bool x, const bool y)
{
	setFlipX(x);
	setFlipY(y);
}

inline const sf::Color& Entity::getColor(void)
{
	return m_color;
}

inline void Entity::setColor(const sf::Color& color)
{
	m_color = color;
}

inline void Entity::setTint(const sf::Color& color)
{
	m_color.r = color.r;
	m_color.g = color.g;
	m_color.b = color.b;
	// Forzamos el setColor para que actualice en la derivada
	setColor(m_color);
}

inline unsigned char Entity::getOpacity(void) const
{
	return m_color.a;
}

inline void Entity::setOpacity(const unsigned char opacity)
{
	m_color.a = opacity;
	// Forzamos el setColor para que actualice en la derivada
	setColor(m_color);
}

inline void Entity::setParent(Entity* entity)
{
	m_parent = entity;
}

inline void Entity::addChild(Entity* entity)
{
	if (entity)
	{
		m_children.push_back(entity);
	}
}

#ifdef BMONKEY_DESIGNER
inline void Entity::updateGrid(const float width, const float height)
{
	m_grid_box.setSize(sf::Vector2f(m_width, m_height));
	m_grid_box.setOrigin(width / 2.f, height / 2.f);
	//m_grid_dot.setPosition(width / 2.f, height / 2.f);
}
#endif

inline void Entity::updateCurrent(sf::Time delta_time)
{
}
