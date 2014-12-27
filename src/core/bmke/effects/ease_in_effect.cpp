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

#include "ease_in_effect.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

EaseInEffect::EaseInEffect(void):
	MoveInEffect(),
	m_tween(nullptr),
	m_pos(0)
{
}

EaseInEffect::~EaseInEffect(void)
{
}

void EaseInEffect::init(Entity* entity, const float delay, const float duration)
{
	MoveInEffect::init(entity, delay, duration);

	if ((getOrigin() == LEFT) || (getOrigin() == RIGHT))
	{
		m_pos = getPosition().x;
	}
	else
	{
		m_pos = getPosition().y;
	}
	// Borramos primero el tween.
	delete m_tween;
	m_tween = new CDBTweener::CTween(&CDBTweener::TWEQ_EXPONENTIAL, CDBTweener::TWEA_OUT, duration, &m_pos, 0);
	m_clock.restart();
}

void EaseInEffect::update(sf::Time delta_time)
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
			setPosition(m_pos, getPosition().y);
		}
		else
		{
			setPosition(getPosition().x, m_pos);
		}
	}
}

} // namespace bmonkey
