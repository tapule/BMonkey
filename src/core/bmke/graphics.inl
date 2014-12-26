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

#ifndef _GRAPHICS_INL_
#define _GRAPHICS_INL_

inline void Graphics::close()
{
	m_window.close();
}

inline bool Graphics::isOpen() const
{
	return m_window.isOpen();
}

inline sf::Vector2u Graphics::getSize() const
{
	return m_window.getSize();
}

inline void Graphics::clear(const sf::Color& color)
{
	m_window.clear(color);
}

inline void Graphics::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
	m_window.draw(drawable, states);
}

inline void Graphics::display()
{
	m_window.display();
}

inline sf::RenderWindow* Graphics::getRenderWindow(void)
{
	return &m_window;
}

#endif // _GRAPHICS_INL_
