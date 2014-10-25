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

#include "hardroll_in_effect.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

HardrollInEffect::HardrollInEffect(void):
	Effect(),
	m_tween(nullptr),
	m_scale(0),
	m_rotation(0)
{
}

HardrollInEffect::~HardrollInEffect(void)
{
}

void HardrollInEffect::init(Entity* entity, const float delay, const float duration)
{
	Effect::init(entity, delay, duration);

	m_scale = 0.f;
	m_rotation = 360.f;
	m_tween = new CDBTweener::CTween(&CDBTweener::TWEQ_ELASTIC, CDBTweener::TWEA_OUT, duration, &m_scale, 1.f);
	m_tween->addValue(&m_rotation, 0.f);
	m_clock.restart();
}

void HardrollInEffect::update(sf::Time delta_time)
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
		setScale(m_scale, m_scale);
		setRotation(m_rotation);
	}
}

} // namespace bmonkey
