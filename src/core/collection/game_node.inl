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


#ifndef _GAME_NODE_INL_
#define _GAME_NODE_INL_

inline GameNode* GameNode::getNext(void)
{
	return m_next;
}

inline void GameNode::setNext(GameNode* next)
{
	m_next = next;
}

inline GameNode* GameNode::getPrev(void)
{
	return m_prev;
}

inline void GameNode::setPrev(GameNode* prev)
{
	m_prev = prev;
}

inline GameNode* GameNode::getNextFiltered(void)
{
	return m_next_filtered;
}

inline void GameNode::setNextFiltered(GameNode* next)
{
	m_next_filtered = next;
}

inline GameNode* GameNode::getPrevFiltered(void)
{
	return m_prev_filtered;
}

inline void GameNode::setPrevFiltered(GameNode* prev)
{
	m_prev_filtered = prev;
}

inline Game* GameNode::getGame(void)
{
	return m_game;
}

inline void GameNode::setGame(Game* game)
{
	m_game = game;
}

inline Glib::ustring GameNode::itemName(void)
{
	assert(m_game);

	return m_game->name;
}

inline Glib::ustring GameNode::itemTitle(void)
{
	assert(m_game);

	return m_game->title;
}

inline Glib::ustring GameNode::itemResourcesDir(void)
{
	assert(m_game);

	return m_game->resources_dir;
}

#endif // _GAME_NODE_HPP_
