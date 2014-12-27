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

#include "effect_factory.hpp"
#include "effects/back_in_effect.hpp"
#include "effects/bounce_in_effect.hpp"
#include "effects/ease_in_effect.hpp"
#include "effects/elastic_in_effect.hpp"
#include "effects/fade_in_effect.hpp"
#include "effects/hardroll_in_effect.hpp"
#include "effects/pop_in_effect.hpp"
#include "effects/roll_in_effect.hpp"
#include "effects/rotate_in_effect.hpp"

#include "effects/back_out_effect.hpp"
#include "effects/fade_out_effect.hpp"

#include "effects/ease_effect.hpp"
#include "effects/fade_effect.hpp"

namespace bmonkey{

Effect* EffectFactory::create(const Type type)
{
	Effect* effect = nullptr;
	MoveInEffect* move_in = nullptr;
	MoveOutEffect* move_out = nullptr;

	switch (type)
	{
	case BACK_IN:
	case LEFT_BACK_IN:
		effect = new BackInEffect();
		break;
	case RIGHT_BACK_IN:
		move_in = new BackInEffect();
		move_in->setOrigin(MoveInEffect::RIGHT);
		effect = move_in;
		break;
	case TOP_BACK_IN:
		move_in = new BackInEffect();
		move_in->setOrigin(MoveInEffect::TOP);
		effect = move_in;
		break;
	case BOTTOM_BACK_IN:
		move_in = new BackInEffect();
		move_in->setOrigin(MoveInEffect::BOTTOM);
		effect = move_in;
		break;
	case BOUNCE_IN:
	case LEFT_BOUNCE_IN	:
		effect = new BounceInEffect();
		break;
	case RIGHT_BOUNCE_IN:
		move_in = new BounceInEffect();
		move_in->setOrigin(MoveInEffect::RIGHT);
		effect = move_in;
		break;
	case TOP_BOUNCE_IN:
		move_in = new BounceInEffect();
		move_in->setOrigin(MoveInEffect::TOP);
		effect = move_in;
		break;
	case BOTTOM_BOUNCE_IN:
		move_in = new BounceInEffect();
		move_in->setOrigin(MoveInEffect::BOTTOM);
		effect = move_in;
		break;
	case EASE_IN:
	case LEFT_EASE_IN:
		effect = new EaseInEffect();
		break;
	case RIGHT_EASE_IN:
		move_in = new EaseInEffect();
		move_in->setOrigin(MoveInEffect::RIGHT);
		effect = move_in;
		break;
	case TOP_EASE_IN:
		move_in = new EaseInEffect();
		move_in->setOrigin(MoveInEffect::TOP);
		effect = move_in;
		break;
	case BOTTOM_EASE_IN:
		move_in = new EaseInEffect();
		move_in->setOrigin(MoveInEffect::BOTTOM);
		effect = move_in;
		break;
	case ELASTIC_IN:
	case LEFT_ELASTIC_IN:
		effect = new ElasticInEffect();
		break;
	case RIGHT_ELASTIC_IN:
		move_in = new ElasticInEffect();
		move_in->setOrigin(MoveInEffect::RIGHT);
		effect = move_in;
		break;
	case TOP_ELASTIC_IN:
		move_in = new ElasticInEffect();
		move_in->setOrigin(MoveInEffect::TOP);
		effect = move_in;
		break;
	case BOTTOM_ELASTIC_IN:
		move_in = new ElasticInEffect();
		move_in->setOrigin(MoveInEffect::BOTTOM);
		effect = move_in;
		break;
	case FADE_IN:
		effect = new FadeInEffect();
		break;
	case HARDROLL_IN:
		effect = new HardrollInEffect();
		break;
	case POP_IN:
		effect = new PopInEffect();
		break;
	case ROLL_IN:
		effect = new RollInEffect();
		break;
	case ROTATE_IN:
		effect = new RotateInEffect();
		break;

	// Efectos de salida de escena
	case BACK_OUT:
	case LEFT_BACK_OUT:
		effect = new BackOutEffect();
		break;
	case RIGHT_BACK_OUT:
		move_out = new BackOutEffect();
		move_out->setDestination(MoveOutEffect::RIGHT);
		effect = move_out;
		break;
	case TOP_BACK_OUT:
		move_out = new BackOutEffect();
		move_out->setDestination(MoveOutEffect::TOP);
		effect = move_out;
		break;
	case BOTTOM_BACK_OUT:
		move_out = new BackOutEffect();
		move_out->setDestination(MoveOutEffect::BOTTOM);
		effect = move_out;
		break;
	case FADE_OUT:
		effect = new FadeOutEffect();
		break;

	// Efectos de posición en escena
	case EASE:
		effect = new EaseEffect();
		break;
	case FADE:
		effect = new FadeEffect();
		break;
	default:
		effect = nullptr;
	}

	return effect;
}

} // namespace bmonkey
