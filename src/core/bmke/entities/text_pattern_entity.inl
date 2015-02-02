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

#ifndef _TEXT_PATTERN_ENTITY_INL_
#define _TEXT_PATTERN_ENTITY_INL_

inline void TextPatternEntity::setPivot(Pivot pivot)
{
	TextEntity::setPivot(pivot);
}

inline void TextPatternEntity::setColor(const sf::Color& color)
{
	TextEntity::setColor(color);
}

inline sf::Vector2i TextPatternEntity::getSize(void) const
{
	return TextEntity::getSize();
}

inline Glib::ustring TextPatternEntity::getString(void) const
{
	return m_pattern;
}

inline void TextPatternEntity::setString(const Glib::ustring& string)
{
	m_pattern = string;
	m_parser.initFromString(m_pattern);
	m_need_parse = true;
	checkPatterns();
}

inline void TextPatternEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	TextEntity::drawCurrent(target, states);
}

#endif // _TEXT_PATTERN_ENTITY_INL_
