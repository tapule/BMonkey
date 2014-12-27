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

#include "transition_entity.hpp"
#include <cassert>

namespace bmonkey{

TransitionEntity::TransitionEntity(void):
	Entity(),
	m_start_effect(nullptr),
	m_texture(nullptr)
{
}

TransitionEntity::~TransitionEntity(void)
{
	delete m_start_effect;
}

sf::Vector2f TransitionEntity::getSize(void) const
{
/*	sf::Vector2u texture_size;
	sf::Vector2f size;

	if (m_texture)
	{
		texture_size = m_texture->getSize();
		size = getScale();
		size.x = std::abs(size.x) * texture_size.x;
		size.y = std::abs(size.y) * texture_size.y;
	}
	return size;*/

	sf::Vector2u texture_size;
	sf::Vector2f size;
	sf::FloatRect r;

	texture_size = m_texture->getSize();
	r = sf::FloatRect(0.f, 0.f, texture_size.x, texture_size.y);
	r = getTransform().transformRect(r);

	size.x = r.width;
	size.y = r.height;

	return size;
}

void TransitionEntity::setColor(const sf::Color& color)
{
	Entity::setColor(color);
	m_sprite.setColor(color);
}

void TransitionEntity::run(void)
{
	Entity::run();

	// Reseteamos el efecto de entrada
	if (m_start_effect)
	{
		m_start_effect->reset();
	}
}

void TransitionEntity::setTexture(sf::Texture *texture)
{
	sf::FloatRect bounds;

	m_texture = texture;
	m_sprite.setTexture(*m_texture, true);
	// Movemos el origen al centro del sprite
	bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void TransitionEntity::setStartEffect(Effect* effect)
{
	delete m_start_effect;
	m_start_effect = effect;
}

void TransitionEntity::updateCurrent(sf::Time delta_time, const sf::Color& color)
{
	// Si tenemos algún efecto, lo actualizamos
	if (m_start_effect)
	{
		m_start_effect->update(delta_time);
		m_current_color = m_start_effect->getColor();
		m_sprite.setColor(m_current_color);
	}
}

#ifdef BMONKEY_DESIGNER
inline void TransitionEntity::updateGrid(void)
{
	sf::Vector2f size;

	size = getSize();
	m_grid_box.setSize(size);
	m_grid_box.setOrigin(size.x / 2.f, size.y / 2.f);
	//m_grid_dot.setPosition(width / 2.f, height / 2.f);
}
#endif

void TransitionEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_start_effect)
	{
		//states.transform = m_start_effect->getTransform() * states.transform;
		states.transform *= m_start_effect->getTransform();
		states.shader = m_start_effect->getShader();
	}
	target.draw(m_sprite, states);
}


} // namespace bmonkey
