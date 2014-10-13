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

#ifndef _SOUND_MANAGER_HPP_
#define _SOUND_MANAGER_HPP_

#include <SFML/Audio.hpp>
#include <glibmm/ustring.h>
#include <vector>
#include <unordered_map>
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Gestiona los efectos de sonido y la música del sistema
 *
 * Se encarga de mantener y gestionar dos tipos de recursos de audio: Los
 * efectos de sonido y la música de fondo del frontend.
 * Normalmente los sonidos del frontend se cargan una única vez por theme y se
 * mantienen durante su ejecución, por lo que la clase está diseñada para este
 * fin.
 * Proporciona un efecto de sonido especial "SPECIAL" que puede ser usado para
 * reproducciones múltiples de sonidos sin necesidad de limpiar el resto de
 * efectos de sonido.
 * La música de fondo se reproducirá en loop.
 * Se define como singleton, de forma que solamente tendrémos una instancia
 * durante toda la ejecución.
 */
class SoundManager
{
public:

	// Posibles efectos de sonido gestionados por el SoundManager
	enum Effect
	{
		SELECT = 0,		/**< Se emite con el evento Select */
		BACK,			/**< Se emite con el evento Back */
		PREVIOUS,		/**< Se emite con los eventos Platform_Previous, Game_Previous */
		NEXT,			/**< Se emite con los eventos Platform_Next, Game_Next */
		UP,				/**< Se emite con el evento Menu_Up */
		DOWN,			/**< Se emite con el evento Menu_Down */
		LEFT,			/**< Se emite con el evento Menu_Left */
		RIGHT,			/**< Se emite con el evento Menu_Right */
		JUMP_BACKWARD,	/**< Se emite con los eventos Game_Letter_Previous y Game_Jump_Backward */
		JUMP_FORWARD,	/**< Se emite con los eventos Game_Letter_Next y Game_Jump_Forward */
		MENU_OPEN,		/**< Se emite con los eventos de apertura de menús */
		ERROR,			/**< Se emite cuando se genera un evento no permitido */
		SPECIAL,		/**< Sonido especial de carga y descarga rápida */
		COUNT			/**< Contador de sonidos */
	};

protected:

	/**
	 * Constructor de la clase
	 */
	SoundManager(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~SoundManager(void);

	/**
	 * Constructor de copia anulado para reforzar el singleton
	 */
	SoundManager(SoundManager const&);

	/**
	 * Operador de copia anulado para reforzar el singleton
	 */
	SoundManager& operator=(SoundManager const&);

public:

	/**
	 * Obtiene la instancia única del manager
	 * @return Instancia única del manager
	 */
	static SoundManager* getInstance(void);

	/**
	 * Carga un audio para un efecto determinado
	 * @param effect Efecto para el que se cargará el sonido
	 * @param file Path del fichero de audio a cargar
	 * @return true Si se pudo realizar la carga, false en otro caso.
	 * @note La lista de formatos de audio soportados es la siguiente: ogg, wav,
	 * flac, aiff, au, raw, paf, svx, nist, voc, ircam, w64, mat4, mat5 pvf,
	 * htk, sds, avr, sd2, caf, wve, mpc2k, rf64.
	 */
	bool loadSound(const Effect effect, const Glib::ustring& file);

	/**
	 * Reproduce el audio vinculado con el efecto dado
	 * @param effect Effecto a reproducir
	 */
	void playSound(const Effect effect);

	/**
	 * Detiene la reproducción del efecto indicado
	 * @param effect Efecto de sonido a detener
	 */
	void stopSound(const Effect effect);

	/**
	 * Detiene la reproducción de todos los efectos de sonido
	 */
	void stopAllSound(void);

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
	 * Carga el audio para la música de fondo
	 * @param file Path del fichero musical
	 * @return true Si se pudo realizar la carga, false en otro caso
	 * @note La lista de formatos de audio soportados es la siguiente: ogg, wav,
	 * flac, aiff, au, raw, paf, svx, nist, voc, ircam, w64, mat4, mat5 pvf,
	 * htk, sds, avr, sd2, caf, wve, mpc2k, rf64.
	 */
	bool openMusic(const Glib::ustring& file);

	/**
	 * Reproduce la música de fondo
	 */
	void playMusic(void);

	/**
	 * Pausa la reproducción de la música de fondo
	 */
	void pauseMusic(void);

	/**
	 * Detiene la reproducción de la música de fondo
	 */
	void stopMusic(void);

	/**
	 * Obtiene el volumen actual para la música de fondo
	 * @return Volumen actual para la música de fondo
	 */
	float getMusicVolume(void) const;

	/**
	 * Establece el volumen para la música de fondo
	 * @param volume Nuevo volumen en el rango [0..100]
	 */
	void setMusicVolume(const float volume);

	/**
	 * Limpia el SoundManager liberando todos los audios cargados
	 */
	void clear(void);

private:

	std::unordered_map<std::string, sf::SoundBuffer* > m_buffers_map;	/**< Indexa los buffers de los sonidos */
	sf::SoundBuffer* m_special_buffer;		/**< Buffer para el sonido especial */
	std::vector<sf::Sound* > m_sounds;		/**< Vector de sonidos reales */
	sf::Music* m_music;						/**< Música del sound manager */
	float m_sound_volume;					/**< Volumen para los sonidos */
	float m_music_volume;					/**< Volumen para la música */

	static SoundManager* m_sound_manager;	/**< Instancia única del manager */
};

// Inclusión de los métodos inline
#include "sound_manager.inl"

} // namespace bmonkey

#endif // _SOUND_MANAGER_HPP_
