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

#include "sound_manager.hpp"
#include <cassert>

namespace bmonkey{

SoundManager* SoundManager::m_sound_manager = nullptr;

SoundManager::SoundManager(void):
	m_special_buffer(nullptr),
	m_sounds(COUNT, nullptr),
	m_music(nullptr),
	m_sound_volume(100.f),
	m_music_volume(100.f)
{
}

SoundManager::~SoundManager(void)
{
	clear();
}

bool SoundManager::loadSound(const Effect effect, const Glib::ustring& file)
{
	std::unordered_map<std::string, sf::SoundBuffer* >::iterator iter;
	sf::SoundBuffer* buffer;

	assert(effect < COUNT);

	if (file.empty())
	{
		return false;
	}

	// Forzamos el stop del sonido
	stopSound(effect);

	// El sonido especial tiene un buffer independiente para poder ser reutilizado
	if (effect == SPECIAL)
	{
		if (!m_special_buffer)
		{
			m_special_buffer = new sf::SoundBuffer();
		}
		if (!m_special_buffer->loadFromFile(file))
		{
			return false;
		}
		buffer = m_special_buffer;
	}
	else
	{
		// Comprobamos si ya tenemos el buffer de audio cargado
		iter = m_buffers_map.find(file);
		if (iter != m_buffers_map.end() )
		{
			buffer = iter->second;
		}
		else
		{
			buffer = new sf::SoundBuffer();
			// Cargamos el nuevo buffer de sonido y lo almacenamos
			if (!buffer->loadFromFile(file))
			{
				delete buffer;
				return false;
			}
			else
			{
				m_buffers_map[file] = buffer;
			}
		}
	}

	// Creamos el nuevo sonido si es necesario
	if (!m_sounds[effect])
	{
		m_sounds[effect] = new sf::Sound();
		m_sounds[effect]->setVolume(m_sound_volume);
	}
	m_sounds[effect]->setBuffer(*buffer);

	return true;
}

void SoundManager::stopAllSound(void)
{
	int effect;

	for (effect = 0; effect < COUNT; ++effect)
	{
		stopSound(static_cast<Effect>(effect));
	}
}

void SoundManager::setSoundVolume(const float volume)
{
	std::vector<sf::Sound* >::iterator iter;

	if (volume == m_sound_volume)
	{
		return;
	}
	m_sound_volume = volume < 0.f ? 0.f: volume;
	m_sound_volume = m_sound_volume > 100.f ? 100.f: m_sound_volume;

	// Reestablecemos el volumen de todos los sonidos
	for (iter = m_sounds.begin(); iter != m_sounds.end(); ++iter)
	{
		if (*iter)
		{
			(*iter)->setVolume(m_sound_volume);
		}
	}
}

bool SoundManager::openMusic(const Glib::ustring& file)
{
	if (file.empty())
	{
		return false;
	}
	if (!m_music)
	{
		m_music = new sf::Music();
		m_music->setVolume(m_music_volume);
	}
	if (!m_music->openFromFile(file))
	{
		delete m_music;
		return false;
	}
	return true;
}

void SoundManager::clear(void)
{
	std::unordered_map<std::string, sf::SoundBuffer* >::iterator buff_iter;
	std::vector<sf::Sound* >::iterator snd_iter;

	// Paramos todo el sonido
	stopAllSound();
	stopMusic();

	for (buff_iter = m_buffers_map.begin(); buff_iter != m_buffers_map.end(); ++buff_iter)
	{
		delete buff_iter->second;
	}
	m_buffers_map.clear();

	// Eliminamos el buffer del sonido especial
	delete m_special_buffer;
	m_special_buffer = nullptr;

	// Eliminamos los sonidos
	for (snd_iter = m_sounds.begin(); snd_iter != m_sounds.end(); ++snd_iter)
	{
		delete (*snd_iter);
		*snd_iter = nullptr;
	}

	// Eliminamos la música
	delete m_music;
	m_music = nullptr;
}

} // namespace bmonkey
