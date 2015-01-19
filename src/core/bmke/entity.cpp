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
	m_enabled(true),
	m_status(STARTED),
	m_pivot(CENTER),
	m_color(sf::Color(255, 255, 255, 255)),
	m_start_animation(nullptr),
	m_position_animation(nullptr),
	m_current_animation(nullptr),
	m_parent(nullptr)
{
}

Entity::~Entity(void)
{
	std::vector<Entity* >::iterator iter;
	std::vector<Animation* >::iterator aiter;

	for (iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		delete (*iter);
	}

	delete m_start_animation;
	delete m_position_animation;
}

Animation* Entity::getAnimation(Entity::AnimationType type)
{
	if (type == START_ANIMATION)
	{
		return m_start_animation;
	}
	else
	{
		return m_position_animation;
	}
}

void Entity::setAnimation(AnimationType type, Animation* animation)
{
	// Si hay animación la inicializamos
	if (animation)
	{
		animation->init(this);
	}

	if (type == START_ANIMATION)
	{
		delete m_start_animation;
		m_start_animation = animation;
	}
	else
	{
		delete m_position_animation;
		m_position_animation = animation;
	}
}

void Entity::removeChild(Entity* entity)
{
	std::vector<Entity* >::iterator iter;

	assert(entity);

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

void Entity::run(void)
{
	m_status = STARTED;
	// Reseteamos el efecto de entrada y actualizamos el estado de la entidad
	if (m_start_animation)
	{
		m_current_animation = m_start_animation;
	}
	else
	{
		m_current_animation = m_position_animation;
	}

	if (m_current_animation)
	{
		m_current_animation->run();
	}

}

void Entity::stop(void)
{
	m_status = STOPPED;
	if (m_current_animation)
	{
		m_current_animation->stop();
	}
	m_current_animation = nullptr;
}

void Entity::update(sf::Time delta_time, const sf::Color& color)
{
	// Solo actualizamos si la entidad está habilitada y en ejecución
	if (m_enabled && m_status == STARTED)
	{
		// Comprobamos si es necesario avanzar a la siguiente animación
		if (m_current_animation && m_current_animation == m_start_animation && m_current_animation->isFinished())
		{
			m_current_animation = m_position_animation;
			if (m_current_animation)
			{
				m_current_animation->run();
			}
		}
		// Si hay animación la actualizamos
		if (m_current_animation)
		{
			m_current_animation->update(delta_time);
		}
		updateCurrent(delta_time, color);
		updateChildren(delta_time, color);
	}
}

void Entity::updateChildren(sf::Time delta_time, const sf::Color& color)
{
	std::vector<Entity* >::iterator iter;

	for (iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->update(delta_time, color);
	}
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::vector<Entity* >::const_iterator iter;

	// Solo dibujamos si está habilitada
	if (m_enabled)
	{
		states.transform *= getTransform();
		if (m_current_animation)
		{
			states.shader = m_current_animation->getShader();
		}
		drawCurrent(target, states);

		for (iter = m_children.begin(); iter != m_children.end(); ++iter)
		{
			(*iter)->draw(target, states);
		}
	}
}

} // namespace bmonkey
