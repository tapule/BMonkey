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

#include "fade_out_effect.hpp"
#include <cassert>
#include "../entity.hpp"

namespace bmonkey{

FadeOutEffect::FadeOutEffect(const float delay, const float duration):
	Effect(delay, duration),
	m_tween(nullptr),
	m_current_pos(0)
{
}

FadeOutEffect::~FadeOutEffect(void)
{
}

void FadeOutEffect::init(Entity* entity)
{
	Effect::init(entity);
	m_entity_color = entity->getColor();
}

void FadeOutEffect::run(void)
{
	// Indicamos que estamos ejecutando
	m_finished = false;
	m_current_pos = m_entity_color.a;
	// Borramos primero el tween.
	delete m_tween;
	m_tween = new CDBTweener::CTween(&CDBTweener::TWEQ_QUADRATIC, CDBTweener::TWEA_OUT, getDuration(), &m_current_pos, 0);
	m_clock.restart();
}

void FadeOutEffect::stop(void)
{
	m_finished = true;
	m_entity->setColor(m_entity_color);
}

void FadeOutEffect::update(sf::Time delta_time)
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
		m_entity->setOpacity(static_cast<unsigned char>(m_current_pos));
	}
}

} // namespace bmonkey
