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

#include "animation_factory.hpp"
#include "animations/back_in_animation.hpp"
#include "animations/bounce_in_animation.hpp"
#include "animations/ease_in_animation.hpp"
#include "animations/elastic_in_animation.hpp"
#include "animations/fade_in_animation.hpp"
#include "animations/hardroll_in_animation.hpp"
#include "animations/pop_in_animation.hpp"
#include "animations/roll_in_animation.hpp"
#include "animations/rotate_in_animation.hpp"

#include "animations/back_out_animation.hpp"
#include "animations/fade_out_animation.hpp"

#include "animations/ease_animation.hpp"
#include "animations/fade_animation.hpp"

namespace bmonkey{

Animation* AnimationFactory::create(const Type type, const float delay, const float duration)
{
	Animation* animation = nullptr;
	MoveInAnimation* move_in = nullptr;
	MoveOutAnimation* move_out = nullptr;
	EaseAnimation* ease = nullptr;

	switch (type)
	{
	case LEFT_BACK_IN:
		animation = new BackInAnimation(delay, duration);
		break;
	case RIGHT_BACK_IN:
		move_in = new BackInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::RIGHT);
		animation = move_in;
		break;
	case TOP_BACK_IN:
		move_in = new BackInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::TOP);
		animation = move_in;
		break;
	case BOTTOM_BACK_IN:
		move_in = new BackInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::BOTTOM);
		animation = move_in;
		break;
	case LEFT_BOUNCE_IN	:
		animation = new BounceInAnimation(delay, duration);
		break;
	case RIGHT_BOUNCE_IN:
		move_in = new BounceInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::RIGHT);
		animation = move_in;
		break;
	case TOP_BOUNCE_IN:
		move_in = new BounceInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::TOP);
		animation = move_in;
		break;
	case BOTTOM_BOUNCE_IN:
		move_in = new BounceInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::BOTTOM);
		animation = move_in;
		break;
	case LEFT_EASE_IN:
		animation = new EaseInAnimation(delay, duration);
		break;
	case RIGHT_EASE_IN:
		move_in = new EaseInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::RIGHT);
		animation = move_in;
		break;
	case TOP_EASE_IN:
		move_in = new EaseInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::TOP);
		animation = move_in;
		break;
	case BOTTOM_EASE_IN:
		move_in = new EaseInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::BOTTOM);
		animation = move_in;
		break;
	case LEFT_ELASTIC_IN:
		animation = new ElasticInAnimation(delay, duration);
		break;
	case RIGHT_ELASTIC_IN:
		move_in = new ElasticInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::RIGHT);
		animation = move_in;
		break;
	case TOP_ELASTIC_IN:
		move_in = new ElasticInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::TOP);
		animation = move_in;
		break;
	case BOTTOM_ELASTIC_IN:
		move_in = new ElasticInAnimation(delay, duration);
		move_in->setOrigin(MoveInAnimation::BOTTOM);
		animation = move_in;
		break;
	case FADE_IN:
		animation = new FadeInAnimation(delay, duration);
		break;
	case HARDROLL_IN:
		animation = new HardrollInAnimation(delay, duration);
		break;
	case POP_IN:
		animation = new PopInAnimation(delay, duration);
		break;
	case ROLL_IN:
		animation = new RollInAnimation(delay, duration);
		break;
	case ROTATE_IN:
		animation = new RotateInAnimation(delay, duration);
		break;

	// Efectos de salida de escena
	case LEFT_BACK_OUT:
		animation = new BackOutAnimation(delay, duration);
		break;
	case RIGHT_BACK_OUT:
		move_out = new BackOutAnimation(delay, duration);
		move_out->setDestination(MoveOutAnimation::RIGHT);
		animation = move_out;
		break;
	case TOP_BACK_OUT:
		move_out = new BackOutAnimation(delay, duration);
		move_out->setDestination(MoveOutAnimation::TOP);
		animation = move_out;
		break;
	case BOTTOM_BACK_OUT:
		move_out = new BackOutAnimation(delay, duration);
		move_out->setDestination(MoveOutAnimation::BOTTOM);
		animation = move_out;
		break;
	case FADE_OUT:
		animation = new FadeOutAnimation(delay, duration);
		break;

	// Efectos de posición en escena
	case EASE_X:
		animation = new EaseAnimation(delay, duration);
		break;
	case EASE_Y:
		ease = new EaseAnimation(delay, duration);
		ease->setAxis(EaseAnimation::Y);
		animation = ease;
		break;
	case FADE:
		animation = new FadeAnimation(delay, duration);
		break;
	default:
		animation = nullptr;
		break;
	}

	return animation;
}

} // namespace bmonkey
