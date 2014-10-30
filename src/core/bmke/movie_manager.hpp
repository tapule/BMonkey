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

#ifndef _MOVIE_MANAGER_HPP_
#define _MOVIE_MANAGER_HPP_

#include "../../thirdparty/sfeMovie/Movie.hpp"
#include <glibmm/ustring.h>
#include <vector>
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Gestiona los videos del sistema
 *
 * Se encarga de mantener y gestionar los videos que serán usados por el
 * frontend.
 * Actua como una especie de almacén para los videos que se van cargando desde
 * fichero, proporcionando métodos para su carga y descarga.
 * Únicamente permite una instancia de la clase al mismo tiempo.
 */
class MovieManager
{
public:

	/**
	 * Constructor de la clase
	 */
	MovieManager(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~MovieManager(void);

	/**
	 * Carga un nuevo video en el manager y lo devuelve
	 * @param file Path del fichero del video
	 * @return Vídeo cargada o null si no se pudo cargar
	 * @note La lista de contenedores de video soportados es la soportada por
	 * FFMpeg: AIFF, AVI, CAF, DV, FLAC, FLV, MKV, MOV, OGG y WAV
	 */
	sfe::Movie* loadMovie(const Glib::ustring& file);

	/**
	 * Elimina un vídeo del almacen interno del manager
	 * @param Video a eliminar
	 */
	void deleteMovie(sfe::Movie* movie);

	/**
	 * Detiene la reproducción de todos los videos cargados
	 */
	void stopAll(void);

	/**
	 * Obtiene el volumen actual para los videos
	 * @return Volumen actual para los videos
	 */
	float getVolume(void) const;

	/**
	 * Establece el volumen para los videos
	 * @param volume Nuevo volumen en el rango [0..100]
	 */
	void setVolume(const float volume);

	/**
	 * Limpia MovieManager liberando todos los videos cargados
	 */
	void clean(void);

private:

	static bool m_instantiated;		/**< Indica si ya hay una instancia de la clase */

	std::vector<sfe::Movie* > m_movies;		/**< Almacen de vídeos */
	float m_volume;							/**< Volumen para los vídeos */
};

} // namespace bmonkey

#endif // _MOVIE_MANAGER_HPP_
