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

#include "ease_animation.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

#define EASE_OFFSET 25.f

EaseAnimation::EaseAnimation(const float delay, const float duration):
	Animation(delay, duration),
	m_tween(nullptr),
	m_axis(X),
	m_current_pos(0),
	m_dest_pos_a(0),
	m_dest_pos_b(0)
{
}

EaseAnimation::~EaseAnimation(void)
{
	// Forzamos la parada para que restaure las propiedades de la entidad
	stop();
	delete m_tween;
}

void EaseAnimation::init(Entity* entity)
{
	Animation::init(entity);
	m_entity_pos = entity->getPosition();
}

void EaseAnimation::run(void)
{
	// Indicamos que estamos ejecutando
	m_finished = false;
	// Ajustamos origen y destinos iniciales
	if (m_axis == X)
	{
		m_dest_pos_a = m_entity_pos.x - EASE_OFFSET;
		m_dest_pos_b = m_entity_pos.x + EASE_OFFSET;
		m_current_pos = m_entity_pos.x;
	}
	else
	{
		m_dest_pos_a = m_entity_pos.y - EASE_OFFSET;
		m_dest_pos_b = m_entity_pos.y + EASE_OFFSET;
		m_current_pos = m_entity_pos.y;
	}
	// Borramos primero el tween.
	delete m_tween;
	m_tween = new CDBTweener::CTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_OUT, getDuration(), &m_current_pos, m_dest_pos_a);
	m_clock.restart();
}

void EaseAnimation::stop(void)
{
	m_finished = true;
	m_entity->setPosition(m_entity_pos);
}

void EaseAnimation::update(sf::Time delta_time)
{
	// Comprobamos si hemos sobrepasado el delay
	if (!m_finished && m_clock.getElapsedTime().asSeconds() > getDelay())
	{
		// Comprobamos si en el último update se llegó al fin
		if (m_tween->isFinished())
		{
			if (m_current_pos == m_dest_pos_a)
			{
				(m_tween->getValues())[0]->m_fTarget = m_dest_pos_b;
			}
			else
			{
				(m_tween->getValues())[0]->m_fTarget = m_dest_pos_a;
			}
			m_tween->setElapsedSec(0.f);
		}
		m_tween->step(delta_time.asSeconds());
		if (m_axis == X)
		{
			m_entity->setPosition(m_current_pos, m_entity_pos.y);
		}
		else
		{
			m_entity->setPosition(m_entity_pos.x, m_current_pos);
		}
	}
}

void EaseAnimation::setAxis(const Axis axis)
{
	m_axis = axis;
}

} // namespace bmonkey
