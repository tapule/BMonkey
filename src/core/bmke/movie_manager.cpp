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

#include "movie_manager.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>

namespace bmonkey{

MovieManager* MovieManager::m_movie_manager = nullptr;

MovieManager::MovieManager(void):
	m_volume(100.f)
{
}

MovieManager::~MovieManager(void)
{
	clear();
}

MovieManager* MovieManager::getInstance(void)
{
	if (!m_movie_manager)
	{
		m_movie_manager = new MovieManager();
	}
	return m_movie_manager;
}

sfe::Movie* MovieManager::loadMovie(const Glib::ustring& file)
{
	sfe::Movie* movie = nullptr;

	if (file.empty())
	{
		return nullptr;
	}

	movie = new sfe::Movie();
	movie->setVolume(m_volume);
	if (!movie->openFromFile(file))
	{
		delete movie;
		return nullptr;
	}
	m_movies.push_back(movie);
	return movie;
}

void MovieManager::deleteMovie(sfe::Movie* movie)
{
	std::vector<sfe::Movie* >::iterator iter;

	if (!movie)
	{
		return;
	}

	// Buscamos el vídeo
	for (iter = m_movies.begin(); iter != m_movies.end(); ++iter)
	{
		if ((*iter) == movie)
		{
			(*iter)->stop();
			delete (*iter);
			m_movies.erase(iter);
			return;
		}
	}
	return;
}

void MovieManager::stopAll(void)
{
	std::vector<sfe::Movie* >::iterator iter;

	for (iter = m_movies.begin(); iter != m_movies.end(); ++iter)
	{
		(*iter)->stop();
	}
}

float MovieManager::getVolume(void) const
{
	return m_volume;
}

void MovieManager::setVolume(const float volume)
{
	std::vector<sfe::Movie* >::iterator iter;

	m_volume = (volume < 0.f ? 0.f: volume);
	m_volume = (m_volume > 100.f ? 100.f : m_volume);
	for (iter = m_movies.begin(); iter != m_movies.end(); ++iter)
	{
		(*iter)->setVolume(m_volume);
	}
}

// CHECKME: Parece que falla si se llama desde el destructor ????
void MovieManager::clear(void)
{
	std::vector<sfe::Movie* >::iterator iter;

	// Buscamos el vídeo
	for (iter = m_movies.begin(); iter != m_movies.end(); ++iter)
	{
		(*iter)->stop();
		delete (*iter);
	}
	m_movies.clear();
}

} // namespace bmonkey
