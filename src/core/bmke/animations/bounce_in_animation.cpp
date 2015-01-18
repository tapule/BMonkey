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

#include "bounce_in_animation.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

BounceInAnimation::BounceInAnimation(const float delay, const float duration):
	MoveInAnimation(delay, duration),
	m_tween(nullptr),
	m_current_pos(0)
{
}

BounceInAnimation::~BounceInAnimation(void)
{
	delete m_tween;
}

void BounceInAnimation::run(void)
{
	float dest_pos;

	// Indicamos que estamos ejecutando
	m_finished = false;
	if ((getOrigin() == LEFT) || (getOrigin() == RIGHT))
	{
		m_current_pos = m_start_pos.x;
		dest_pos = m_entity_pos.x;
		m_entity->setPosition(m_current_pos, m_entity_pos.y);
	}
	else
	{
		m_current_pos = m_start_pos.y;
		dest_pos = m_entity_pos.y;
		m_entity->setPosition(m_entity_pos.x, m_current_pos);
	}
	// Borramos primero el tween.
	delete m_tween;
	m_tween = new CDBTweener::CTween(&CDBTweener::TWEQ_BOUNCE, CDBTweener::TWEA_OUT, getDuration(), &m_current_pos, dest_pos);
	m_clock.restart();
}

void BounceInAnimation::update(sf::Time delta_time)
{
	// Comprobamos si hemos sobrepasado el delay
	if (!m_finished && m_clock.getElapsedTime().asSeconds() > getDelay())
	{
		// Comprobamos si en el último update se llegó al fin
		if (m_tween->isFinished())
		{
			m_finished = true;
			return;
		}
		m_tween->step(delta_time.asSeconds());
		if ((getOrigin() == LEFT) || (getOrigin() == RIGHT))
		{
			m_entity->setPosition(m_current_pos, m_entity_pos.y);
		}
		else
		{
			m_entity->setPosition(m_entity_pos.x, m_current_pos);
		}
	}
}

} // namespace bmonkey
