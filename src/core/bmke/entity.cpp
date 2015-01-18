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
	m_status(STOPPED),
	m_selected(false),
#else
	m_status(STARTED),
#endif
	m_flip(Vector2b(false, false)),
	m_color(sf::Color(255, 255, 255, 255)),
	m_parent(nullptr),
	m_cyclic_animations(false),
	m_current_animation(-1)
{
#ifdef BMONKEY_DESIGNER
	// Inicialización del grid de selección
	m_grid_box.setOutlineThickness(2.f);
	m_grid_box.setOutlineColor(sf::Color::Yellow);
	m_grid_box.setFillColor(sf::Color::Transparent);

	m_grid_dot.setOutlineThickness(0.f);
	m_grid_dot.setFillColor(sf::Color::Yellow);
	m_grid_dot.setSize(sf::Vector2f(10.f, 10.f));
	m_grid_dot.setOrigin(5.f, 5.f);
#endif
}

Entity::~Entity(void)
{
	std::vector<Entity* >::iterator iter;
	std::vector<Animation* >::iterator eiter;

	for (iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		delete (*iter);
	}

	for (eiter = m_animations.begin(); eiter != m_animations.end(); ++eiter)
	{
		delete (*eiter);
	}

}

void Entity::setFlip(const bool x, const bool y)
{
	sf::Vector2f scale;

	scale = getScale();

	if (x == !m_flip.x)
	{
		scale.x *= -1;
	}
	if (y == !m_flip.y)
	{
		scale.y *= -1;
	}
	setScale(scale);

	m_flip.x = x;
	m_flip.y = y;
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

#ifdef BMONKEY_DESIGNER
void Entity::clearAnimations(void)
{
	std::vector<Animation* >::iterator iter;

	for (iter = m_animations.begin(); iter != m_animations.end(); ++iter)
	{
		delete (*iter);
	}
	m_animations.clear();
	m_current_animation = -1;
}
#endif

void Entity::run(void)
{
	m_status = STARTED;
	if (!m_animations.empty())
	{
		m_current_animation = 0;
		m_animations[m_current_animation]->run();
	}
}

#ifdef BMONKEY_DESIGNER
void Entity::stop(void)
{
	m_status = STOPPED;
	if (m_current_animation >= 0)
	{
		m_animations[m_current_animation]->stop();
	}
	m_current_animation = -1;
}
#endif


void Entity::update(sf::Time delta_time, const sf::Color& color)
{
	// Solo actualizamos si la entidad está en ejecución
	if (m_status == STARTED)
	{
		// Comprobamos si es necesario avanzar a la siguiente animación
		if ((m_current_animation >= 0) && m_animations[m_current_animation]->isFinished())
		{
			++m_current_animation;
			// Comprobamos si necesitamos reajustar el ciclado de animaciones
			if (m_current_animation == m_animations.size())
			{
				if (m_cyclic_animations)
				{
					m_current_animation = 0;
					m_animations[m_current_animation]->run();
				}
				else
				{
					--m_current_animation;
				}
			}
			else
			{
				m_animations[m_current_animation]->run();
			}
		}
		// Si hay animación la actualizamos
		if (m_current_animation >= 0)
		{
			m_animations[m_current_animation]->update(delta_time);
		}
		updateCurrent(delta_time, color);
		updateChildren(delta_time, color);
	}
#ifdef BMONKEY_DESIGNER
	if (m_selected && (m_status == STOPPED))
	{
		updateGrid();
	}
#endif
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

	states.transform *= getTransform();
	if (m_current_animation >= 0)
	{
		states.shader = m_animations[m_current_animation]->getShader();
	}
	drawCurrent(target, states);

	for (iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->draw(target, states);
	}

#ifdef BMONKEY_DESIGNER
	// Solamente dibujamos el grid si está seleccionada y parada
	if (m_selected && (m_status == STOPPED))
	{
		drawGrid(target, states);
	}
#endif
}

#ifdef BMONKEY_DESIGNER
void Entity::drawGrid(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Transformable transformable;
	// Para dibujar el grid, quitamos cualquier shader
	/* states.shader = nullptr;*/
	transformable.setPosition(getPosition());
	transformable.setRotation(getRotation());
	states.transform = transformable.getTransform();
	target.draw(m_grid_box, states);
	target.draw(m_grid_dot, states);
}
#endif

} // namespace bmonkey
