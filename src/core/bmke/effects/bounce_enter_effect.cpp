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

#include "bounce_enter_effect.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

BounceEnterEffect::BounceEnterEffect(void):
	Effect(),
	m_tween(nullptr),
	m_pos(0)
{
}

BounceEnterEffect::~BounceEnterEffect(void)
{
}

void BounceEnterEffect::init(const sf::Vector2u& win_size, Entity* entity, const float delay, const float duration, const StartFrom from)
{
	Effect::init(win_size, entity, delay, duration, from);
	if (m_tween)
	{
		delete m_tween;
	}
	switch (from)
	{
	case LEFT:
	case RIGHT:
		m_pos = getPosition().x;
		break;
	case TOP:
	case BOTTOM:
		m_pos = getPosition().y;
		break;
	case POSITION:
		break;
	}
	m_tween = new CDBTweener::CTween(&CDBTweener::TWEQ_BOUNCE, CDBTweener::TWEA_OUT, duration, &m_pos, 0);
	m_clock.restart();
}

void BounceEnterEffect::update(sf::Time delta_time)
{
	// Comprobamos si hemos sobrepasado el delay
	if (!m_finished && m_clock.getElapsedTime().asSeconds() > m_delay)
	{
		// Comprobamos si en el último update se llegó al fin
		if (m_tween->isFinished())
		{
			m_finished = true;
			return;
		}
		m_tween->step(delta_time.asSeconds());
		switch (m_start_from)
		{
		case LEFT:
		case RIGHT:
			setPosition(m_pos, getPosition().y);
			break;
		case TOP:
		case BOTTOM:
			setPosition(getPosition().x, m_pos);
			break;
		case POSITION:
			break;
		}
	}
}

void BounceEnterEffect::reset(void)
{
	Effect::reset();
}

} // namespace bmonkey
