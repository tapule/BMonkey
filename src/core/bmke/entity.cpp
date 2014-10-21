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

#include "entity.hpp"
#include <cassert>

namespace bmonkey{

Entity::Entity(void):
#ifdef BMONKEY_DESIGNER
	m_enabled(true),
	m_blocked(false),
	m_selected(false),
#endif
	m_status(STOPPED),
	m_width(0),
	m_height(0),
	m_flipx(false),
	m_flipy(false),
	m_color(sf::Color::Transparent),
	m_start_effect(nullptr),
	m_place_effect(nullptr),
	m_current_effect(nullptr),
	m_parent(nullptr)
{
#ifdef BMONKEY_DESIGNER
	// Inicialización del grid de selección
	m_grid_box.setOutlineThickness(2.f);
	m_grid_box.setOutlineColor(sf::Color::Yellow);
	m_grid_box.setFillColor(sf::Color::Transparent);

	m_grid_dot.setOutlineThickness(0.f);
	m_grid_dot.setFillColor(sf::Color::Yellow);
	m_grid_dot.setSize(sf::Vector2f(5.f, 5.f));
	m_grid_dot.setOrigin(2.5f, 2.5f);
#endif
}

Entity::~Entity(void)
{
	std::vector<Entity* >::iterator iter;

	delete m_start_effect;
	delete m_place_effect;

	for (iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		delete (*iter);
	}
}

void Entity::setSize(const float width, const float height)
{
	m_width = width;
	m_height = height;
	updateGrid(m_width, m_height);
}

void Entity::setFlip(const bool x, const bool y)
{
	sf::Vector2f scale;

	scale = getScale();

	if ((x && !m_flipx) || (!x && m_flipx))
	{
		scale.x *= -1;
	}

	if ((y && !m_flipy) || (!y && m_flipy))
	{
		scale.y *= -1;
	}

	setScale(scale);

	m_flipx = x;
	m_flipy = y;
}

unsigned char Entity::getOpacity(void)
{
	if (m_current_effect)
	{
		return m_current_effect->getOpacity();
	}
	else
	{
		return m_color.a;
	}
}

void Entity::setStartEffect(Effect* effect)
{
	delete m_start_effect;
	m_start_effect = effect;
}

void Entity::setPlaceEffect(Effect* effect)
{
	delete m_place_effect;
	m_place_effect = effect;
}

void Entity::removeChild(Entity* entity)
{
	std::vector<Entity* >::iterator iter;

	if (entity)
	{
		for (iter = m_children.begin(); iter != m_children.end(); ++iter)
		{
			if ((*iter) == entity)
			{
				delete (*iter);
				m_children.erase(iter);
				return;
			}
		}
	}
}

void Entity::update(sf::Time delta_time)
{
	switch (m_status)
	{
	// Si estaba detenida, la ejecutamos de nuevo
	case STOPPED:
		// Comprobamos si tenemos efecto de entrada
		if (m_start_effect)
		{
			m_status = STARTED;
			m_current_effect = m_start_effect;
		}
		else
		{
			m_status = PLACED;
			m_current_effect = m_place_effect;
		}
		break;
	// Si estaba entrando, comprobamos si ha terminado
	case STARTED:
		if (m_start_effect && m_start_effect->isFinished())
		{
			m_status = PLACED;
			m_current_effect = m_place_effect;
		}
		break;
	}
	// Si tenemos algún efecto, lo actualizamos
	if (m_current_effect)
	{
		m_current_effect->update(delta_time);
	}
	updateCurrent(delta_time);
	updateChildren(delta_time);
}

void Entity::reset(void)
{
	// Si tenemos efectos, los reseteamos
	if (m_start_effect)
	{
		m_start_effect->reset();
	}
	if (m_place_effect)
	{
		m_place_effect->reset();
	}
	m_status = STOPPED;
	m_current_effect = nullptr;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::vector<Entity* >::const_iterator iter;

	states.transform *= getTransform();
	if (m_current_effect)
	{
		states.transform *= m_current_effect->getTransform();
		states.shader = m_current_effect->getShader();
	}

	drawCurrent(target, states);

	for (iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->draw(target, states);
	}

#ifdef BMONKEY_DESIGNER
	if (m_selected)
	{
		drawGrid(target, states);
	}
#endif
}

#ifdef BMONKEY_DESIGNER
void Entity::drawGrid(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Para dibujar el grid, quitamos cualquier shader
	states.shader = nullptr;
	target.draw(m_grid_box, states);
	target.draw(m_grid_dot, states);
}
#endif

void Entity::updateChildren(sf::Time delta_time)
{
	std::vector<Entity* >::iterator iter;

	if (m_status != STOPPED)
	{
		for (iter = m_children.begin(); iter != m_children.end(); ++iter)
		{
			(*iter)->update(delta_time);
		}
	}
}

} // namespace bmonkey
