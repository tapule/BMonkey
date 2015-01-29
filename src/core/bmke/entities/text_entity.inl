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

#ifndef _TEXT_ENTITY_INL_
#define _TEXT_ENTITY_INL_

inline void TextEntity::setColor(const sf::Color& color)
{
	Entity::setColor(color);
}

inline sf::Font* TextEntity::getFont(void)
{
	return m_font;
}

inline Glib::ustring TextEntity::getString(void) const
{
	return m_string;
}

inline unsigned int TextEntity::getCharacterSize(void) const
{
	return m_character_size;
}

inline TextEntity::Style TextEntity::getStyle(void)
{
	return m_style;
}

inline const sf::Color& TextEntity::getTextColor(void)
{
	return m_text_color;
}

inline void TextEntity::setTextColor(const sf::Color& color)
{
	m_text_color = color;
	m_outline_color.a = color.a;
}

inline unsigned int TextEntity::getMaxLength(void)
{
	return m_max_length;
}

inline void TextEntity::setMaxLength(const unsigned int length)
{
	m_max_length = length;
	setString(m_string);
}

inline bool TextEntity::getForceUppercase(void)
{
	return m_force_uppercase;
}

inline bool TextEntity::getOutlineEnabled(void) const
{
	return m_outline_enabled;
}

inline const sf::Color& TextEntity::getOutlineColor(void)
{
	return m_outline_color;
}

inline void TextEntity::setOutlineColor(const sf::Color& color)
{
	m_outline_color = color;
	m_outline_color.a = m_text_color.a;
}

inline bool TextEntity::getShadowEnabled(void) const
{
	return m_shadow_enabled;
}

inline void TextEntity::setShadowEnabled(const bool enabled)
{
	m_shadow_enabled = enabled;
}

inline const sf::Color& TextEntity::getShadowColor(void)
{
	return m_shadow_color;
}

inline void TextEntity::setShadowColor(const sf::Color& color)
{
	m_shadow_color = color;
}

inline sf::Vector2i TextEntity::getShadowOffset(void) const
{
	return m_shadow_offset;
}

inline void TextEntity::setShadowOffset(const sf::Vector2i& offset)
{
	setShadowOffset(offset.x, offset.y);
}

inline void TextEntity::updateCurrent(sf::Time delta_time, const sf::Color& color)
{
}

#endif // _TEXT_ENTITY_INL_
