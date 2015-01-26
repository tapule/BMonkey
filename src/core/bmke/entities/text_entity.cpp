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

#include "text_entity.hpp"
#include <cassert>
#include <cmath>
#include <SFML/System.hpp>
#include <string>
#include <algorithm>


namespace bmonkey{

// El borde tiene un grosor predeterminado de 2 pixeles
#define OUTLINE_THICKNESS 2.f

TextEntity::TextEntity(FontLibrary* font_library):
	Entity(),
	m_font_library(font_library),
	m_font(font_library->getSystemFont()),
	m_character_size(30),
	m_style(REGULAR),
	m_text_color(sf::Color::White),
	m_force_uppercase(false),
	m_outline_enabled(true),
	m_outline_color(sf::Color::Black),
	m_shadow_enabled(true),
	m_shadow_color(sf::Color::Transparent),
	m_shadow_offset(sf::Vector2i(0, 0)),
	m_shadow_position(sf::Vector2f(0.f, 0.f))

{
	assert(m_font_library);

	// Por defecto fijamos la fuente del sistema
	m_text.setFont(*m_font);
}

TextEntity::~TextEntity(void)
{
	// Indicamos que se puede eliminar la fuente
	m_font_library->deleteFont(m_font);
}

void TextEntity::setPivot(Pivot pivot)
{
	sf::FloatRect bounds;
	sf::Vector2f size;

	m_pivot = pivot;
	bounds = m_text.getLocalBounds();
	// En los textos tenemos que tener en cuenta left y top
	// y no tenemos en cuenta para el cálculo la sombra
	size.x = (bounds.left * 2) + bounds.width;
	size.y = (bounds.top * 2) + bounds.height;
	switch (m_pivot)
	{
	case CENTER:
		setOrigin(size.x / 2.f, size.y / 2.f);
		break;
	case TOP_LEFT:
		setOrigin(0.f, 0.f);
		break;
	case TOP:
		setOrigin(size.x / 2.f, 0.f);
		break;
	case TOP_RIGHT:
		setOrigin(size.x, 0.f);
		break;
	case LEFT:
		setOrigin(0.f, size.y / 2.f);
		break;
	case RIGHT:
		setOrigin(size.x, size.y / 2.f);
		break;
	case BOTTOM_LEFT:
		setOrigin(0.f, size.y);
		break;
	case BOTTOM:
		setOrigin(size.x / 2.f, size.y);
		break;
	case BOTTOM_RIGHT:
		setOrigin(size.x, size.y);
		break;
	}
}

sf::Vector2f TextEntity::getSize(void) const
{
	sf::FloatRect bounds;
	sf::Vector2f size;

	bounds = m_text.getLocalBounds();
	size.x = (bounds.left * 2) + bounds.width;
	size.y = (bounds.top * 2) + bounds.height;

	return size;
}

void TextEntity::setFont(sf::Font* font)
{
	if (font != m_font)
	{
		// Primero eliminamos la fuente previa
		m_font_library->deleteFont(m_font);
		m_font = font;
		m_text.setFont(*m_font);
		// Actualizamos el pivote para posicionarlo en el lugar correcto
		setPivot(m_pivot);
	}
}

void TextEntity::setString(const Glib::ustring& string)
{
	sf::String new_string;

	m_string = string;

	new_string = fromUstring(m_force_uppercase ? string.uppercase() : string);
	m_text.setString(new_string);
	setPivot(m_pivot);
}

void TextEntity::setCharacterSize(const unsigned int size)
{
	m_character_size = size;
	m_text.setCharacterSize(size);
	setPivot(m_pivot);
}

void TextEntity::setStyle(const TextEntity::Style& style)
{
	m_style = style;
	m_text.setStyle(style);
	setPivot(m_pivot);
}

void TextEntity::setForceUppercase(const bool uppercase)
{
	sf::String new_string;

	m_force_uppercase = uppercase;

	new_string = fromUstring(m_force_uppercase ? getString().uppercase() : getString());
	m_text.setString(new_string);
	setPivot(m_pivot);
}

void TextEntity::setOutlineEnabled(const bool enabled)
{
	m_outline_enabled = enabled;

	// Ajustamos la posición de la sombra si se habilitó el outline
	if (m_outline_enabled && (m_shadow_offset.x != 0 || m_shadow_offset.y != 0))
	{
		m_shadow_position.x = m_shadow_offset.x + ((m_shadow_offset.x / std::abs(m_shadow_offset.x)) * OUTLINE_THICKNESS);
		m_shadow_position.y = m_shadow_offset.y + ((m_shadow_offset.y / std::abs(m_shadow_offset.y)) * OUTLINE_THICKNESS);
	}
}

void TextEntity::setShadowOffset(const int ox, const int oy)
{
	m_shadow_offset.x = ox;
	m_shadow_offset.y = oy;

	// Ajustamos la posición del shadow
	if (m_shadow_offset.x != 0 || m_shadow_offset.y != 0)
	{
		// Si tenemos outline, desplazamos la sombra para tener en cuenta el outline
		if (m_outline_enabled)
		{
			m_shadow_position.x = m_shadow_offset.x + ((m_shadow_offset.x / std::abs(m_shadow_offset.x)) * OUTLINE_THICKNESS);
			m_shadow_position.y = m_shadow_offset.y + ((m_shadow_offset.y / std::abs(m_shadow_offset.y)) * OUTLINE_THICKNESS);
		}
		else
		{
			m_shadow_position.x = m_shadow_offset.x;
			m_shadow_position.y = m_shadow_offset.y;
		}
	}
}

void TextEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text text;

	text.setFont(*m_font);
	text.setString(m_text.getString());
	text.setCharacterSize(m_character_size);
	text.setStyle(m_style);

	// Comprobamos si hay que dibujar la sombra
	if (m_shadow_enabled && (m_shadow_offset.x != 0 || m_shadow_offset.y != 0))
	{
		text.setColor(m_shadow_color * m_color);
		text.setPosition(m_shadow_position);
		target.draw(text, states);
	}

	// Comprobamos si hay que sibujar el outline
	if (m_outline_enabled)
	{
		text.setColor(m_outline_color * m_color);
		text.setPosition(-OUTLINE_THICKNESS, -OUTLINE_THICKNESS);
		target.draw(text, states);
		text.setPosition(OUTLINE_THICKNESS, -OUTLINE_THICKNESS);
		target.draw(text, states);
		text.setPosition(OUTLINE_THICKNESS, OUTLINE_THICKNESS);
		target.draw(text, states);
		text.setPosition(-OUTLINE_THICKNESS, OUTLINE_THICKNESS);
		target.draw(text, states);
	}

	text.setColor(m_text_color * m_color);
	text.setPosition(0.f, 0.f);
	target.draw(text, states);
}

sf::String TextEntity::fromUstring(const Glib::ustring& ustring)
{
	sf::String string;
	std::basic_string<unsigned int> buffer;
	Glib::ustring::const_iterator iter;

	// Pequeño truco para convertir de Glib::ustring a sf::String
	for (iter = ustring.begin(); iter!= ustring.end(); ++iter)
	{
		buffer.push_back(*iter);
	}

	string = buffer;
	return string;
}

} // namespace bmonkey
