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

#include "back_out_animation.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

BackOutAnimation::BackOutAnimation(const float delay, const float duration):
	MoveOutAnimation(delay, duration),
	m_tween(nullptr),
	m_current_pos(0)
{
}

BackOutAnimation::~BackOutAnimation(void)
{
	// Forzamos la parada para que restaure las propiedades de la entidad
	stop();
	delete m_tween;
}

void BackOutAnimation::run(void)
{
	float dest_pos;

	// Indicamos que estamos ejecutando
	m_finished = false;
	if ((getDestination() == LEFT) || (getDestination() == RIGHT))
	{
		m_current_pos = m_entity_pos.x;
		dest_pos = m_dest_pos.x;
	}
	else
	{
		m_current_pos = m_entity_pos.y;
		dest_pos = m_dest_pos.y;
	}
	// Borramos primero el tween.
	delete m_tween;
	m_tween = new CDBTweener::CTween(&CDBTweener::TWEQ_BACK, CDBTweener::TWEA_IN, getDuration(), &m_current_pos, dest_pos);
	m_clock.restart();
}

void BackOutAnimation::update(sf::Time delta_time)
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
		if ((getDestination() == LEFT) || (getDestination() == RIGHT))
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
