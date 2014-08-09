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

#include "game_node.hpp"
#include <cassert>

namespace bmonkey{

GameNode::GameNode(void):
	m_game(NULL),
	m_next(NULL),
	m_prev(NULL),
	m_next_filtered(NULL),
	m_prev_filtered(NULL)
{
}

inline Game* GameNode::gameGet(void)
{
	return m_game;
}

inline void GameNode::gameSet(Game* game)
{
	m_game = game;
}

inline Glib::ustring GameNode::getName(void)
{
	assert(m_game);

	return m_game->name;
}

inline Glib::ustring GameNode::getTitle(void)
{
	assert(m_game);

	return m_game->title;
}

inline Glib::ustring GameNode::getResourcesDir(void)
{
	assert(m_game);
	assert(m_game->platform);

	return m_game->platform->getDir();
}

} // namespace bmonkey
