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

#include "volume_manager.hpp"
#include <cassert>

namespace bmonkey{

bool VolumeManager::m_instantiated = false;

VolumeManager::VolumeManager(SoundManager* sound_manager, MovieManager* movie_manager):
	m_sound_manager(sound_manager),
	m_movie_manager(movie_manager),
	m_master_volume(100.f),
	m_sound_volume(100.f),
	m_music_volume(100.f),
	m_movie_volume(100.f)
{
	// Con este assert forzamos una instancia única de la clase
	assert(!m_instantiated);
	m_instantiated = true;

	assert(sound_manager);
	assert(movie_manager);

	m_sound_manager->setSoundVolume(m_sound_volume);
	m_sound_manager->setMusicVolume(m_music_volume);
	m_movie_manager->setVolume(m_movie_volume);
}

VolumeManager::~VolumeManager(void)
{
	// Si se destruye la instancia, permitimos que se cree de nuevo
	m_instantiated = false;
}

void VolumeManager::setVolume(const float master, const float sound, const float music, const float movie)
{
	setMasterVolume(master);
	setSoundVolume(sound);
	setMusicVolume(music);
	setMovieVolume(movie);
}

float VolumeManager::getMasterVolume(void) const
{
	return m_master_volume;
}

void VolumeManager::setMasterVolume(const float volume)
{
	m_master_volume = volume < 0.f ? 0.f: volume;
	m_master_volume = m_master_volume > 100.f ? 100.f: m_master_volume;

	m_sound_manager->setSoundVolume(m_sound_volume * (m_master_volume / 100.f));
	m_sound_manager->setMusicVolume(m_music_volume * (m_master_volume / 100.f));
	m_movie_manager->setVolume(m_movie_volume * (m_master_volume / 100.f));
}

float VolumeManager::getSoundVolume(void) const
{
	return m_sound_volume;
}

void VolumeManager::setSoundVolume(const float volume)
{
	m_sound_volume = volume < 0.f ? 0.f: volume;
	m_sound_volume = m_sound_volume > 100.f ? 100.f: m_sound_volume;

	m_sound_manager->setSoundVolume(m_sound_volume * (m_master_volume / 100.f));
}

float VolumeManager::getMusicVolume(void) const
{
	return m_music_volume;
}

void VolumeManager::setMusicVolume(const float volume)
{
	m_music_volume = volume < 0.f ? 0.f: volume;
	m_music_volume = m_music_volume > 100.f ? 100.f: m_music_volume;

	m_sound_manager->setMusicVolume(m_music_volume * (m_master_volume / 100.f));
}

float VolumeManager::getMovieVolume(void) const
{
	return m_movie_volume;
}

void VolumeManager::setMovieVolume(const float volume)
{
	m_movie_volume = volume < 0.f ? 0.f: volume;
	m_movie_volume = m_movie_volume > 100.f ? 100.f: m_movie_volume;

	m_movie_manager->setVolume(m_movie_volume * (m_master_volume / 100.f));
}

} // namespace bmonkey
