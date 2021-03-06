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

#ifndef _VOLUME_MANAGER_HPP_
#define _VOLUME_MANAGER_HPP_

#include "sound_manager.hpp"
#include "movie_manager.hpp"
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Gestiona los volumenes de sonido, música y videos de forma centralizada.
 *
 * Se encarga de mantener y gestionar los niveles de sonido para los diferentes
 * elementos que pueden reproducirlos. Para ello, se le indica sobre que
 * SoundManager y VideoManager actúa para mantener sincronizados los volumenes
 * actuales.
 * Únicamente permite una instancia de la clase al mismo tiempo.
 */
class VolumeManager
{
public:

	/**
	 * Constuctor de la clase
	 * @param sound_manager SoundManager sobre el que actúa
	 * @param movie_manager MovieManager sobre el que actúa
	 */
	VolumeManager(SoundManager* sound_manager, MovieManager* movie_manager);

	/**
	 * Destructor de la clase
	 */
	virtual ~VolumeManager(void);

	/**
	 * Establece los volúmenes del sonido
	 * @param master Nuevo volumen master en el rango [0..100]
	 * @param sound Nuevo volumen para efectos de sonido en el rango [0..100]
	 * @param music Nuevo volumen para la música de fondo en el rango [0..100]
	 * @param movie Nuevo volumen para los vídeos el rango [0..100]
	 */
	void setVolume(const float master, const float sound, const float music, const float movie);

	/**
	 * Obtiene el volumen maestro actual
	 * @return Volumen maestro actual
	 */
	float getMasterVolume(void) const;

	/**
	 * Establece el volumen maestro
	 * @param volume Nuevo volumen en el rango [0..100]
	 */
	void setMasterVolume(const float volume);

	/**
	 * Obtiene el volumen actual para los efectos de sonido
	 * @return Volumen actual para los efectos de volumen
	 */
	float getSoundVolume(void) const;

	/**
	 * Establece el volumen para los efectos de sonido
	 * @param volume Nuevo volumen en el rango [0..100]
	 */
	void setSoundVolume(const float volume);

	/**
	 * Obtiene el volumen actual para la música de fondo
	 * @return Volumen actual para la música de fondo
	 */
	float getMusicVolume(void) const;

	/**
	 * Establece el volumen la música de fondo
	 * @param volume Nuevo volumen en el rango [0..100]
	 */
	void setMusicVolume(const float volume);

	/**
	 * Obtiene el volumen actual para los videos
	 * @return Volumen actual para los videos
	 */
	float getMovieVolume(void) const;

	/**
	 * Establece el volumen para los videos
	 * @param volume Nuevo volumen en el rango [0..100]
	 */
	void setMovieVolume(const float volume);

private:

	static bool m_instantiated;		/**< Indica si ya hay una instancia de la clase */

	SoundManager* m_sound_manager;	/**< SoundManager que gestiona */
	MovieManager* m_movie_manager;	/**< MovieManager que gestiona */

	float m_master_volume;			/**< Volumen para los sonidos */
	float m_sound_volume;			/**< Volumen para los sonidos */
	float m_music_volume;			/**< Volumen para la música */
	float m_movie_volume;			/**< Volumen para los sonidos */
};

} // namespace bmonkey

#endif // _VOLUME_MANAGER_HPP_
