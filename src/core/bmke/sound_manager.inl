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

#ifndef _SOUND_MANAGER_INL_
#define _SOUND_MANAGER_INL_

inline void SoundManager::playSound(const Effect effect)
{
	assert(effect < COUNT);

	if (m_sounds[effect])
	{
		m_sounds[effect]->play();
	}
}

inline void SoundManager::stopSound(const Effect effect)
{
	assert(effect < COUNT);

	if (m_sounds[effect])
	{
		m_sounds[effect]->stop();
	}
}

inline float SoundManager::getSoundVolume(void) const
{
	return m_sound_volume;
}

inline void SoundManager::playMusic(void)
{
	if (m_music)
	{
		m_music->setLoop(true);
		m_music->play();
	}
}

inline void SoundManager::pauseMusic(void)
{
	if (m_music)
	{
		m_music->pause();
	}
}

inline void SoundManager::stopMusic(void)
{
	if (m_music)
	{
		m_music->stop();
	}
}

inline float SoundManager::getMusicVolume(void) const
{
	return m_music_volume;
}

inline void SoundManager::setMusicVolume(const float volume)
{
	m_music_volume = (volume < 0.f ? 0.f: volume);
	m_music_volume = (m_music_volume > 100.f ? 100.f : m_music_volume);
	if (m_music)
	{
		m_music->setVolume(m_music_volume);
	}
}

#endif // _SOUND_MANAGER_INL
