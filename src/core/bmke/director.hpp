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

#ifndef _DIRECTOR_HPP_
#define _DIRECTOR_HPP_

#include "../../defines.hpp"
#include "../../utils/config.hpp"

#include "../collection/collection.hpp"
#include "graphics.hpp"
#include "control_manager.hpp"
#include "font_manager.hpp"
#include "texture_manager.hpp"
#include "sound_manager.hpp"
#include "movie_manager.hpp"
#include "volume_manager.hpp"
#include "shader_manager.hpp"

#include "entities/transition_entity.hpp"
#include "entities/box_entity.hpp"

namespace bmonkey{

/**
 * Gestiona y coordina las escenas y eventos del frontend
 *
 * El Director se encarga de gestionar las diferentes escenas que se van
 * mostrando durante la ejecución del frontend.
 * Se trata de la pieza principal ya que es donde se aplica toda la lógica de
 * escenas y se controla la interacción del usuario
 * Únicamente permite una instancia de la clase al mismo tiempo.
 */
class Director
{
public:

	/**
	 * Constructor de la clase
	 * @param config Configuración de donde leer y escribir sus parámetros
	 */
	Director(Config* config);

	/**
	 * Destructor de la clase
	 */
	virtual ~Director(void);

	/**
	 * Inicializa el director
	 */
	virtual void init(void);

	/**
	 * Ejecuta el bucle principal del frontend
	 * @return EXIT_SUCCESS si todo fue correcto, EXIT_FAILURE si se produjo
	 * algún error.
	 */
	int run(void);

private:

	/**
	 * Inicializa los volumenes del sistema
	 */
	void volumeInit(void);

	/**
	 * Se encarga de procesar las entradas realizadas por el usuario
	 */
	void processInput(void);

	/**
	 * Actualiza la lógica de la escena
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	void update(sf::Time delta_time);

	/**
	 * Se encarga de actualizar el recuento de fps's
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 */
	void updateFps(sf::Time delta_time);

	/**
	 * Renderiza la escena
	 */
	void draw(void);

	/**
	 * Se encarga de cerrar adecuadamente los sistemas creados
	 */
	void clean(void);


	static bool m_instantiated;		/**< Indica si ya hay una instancia de la clase */

	bool m_init;					/**< Indica si se ha inicializado el director */
	Glib::ustring m_working_dir;	/**< Path del directorio de trabajo */
	Config* m_config;				/**< Sistema de configuración */
	Collection* m_collection;
	Graphics m_graphics;
	ControlManager m_controls;
	FontManager m_fonts;
	SoundManager m_sounds;
	MovieManager m_movies;
	VolumeManager m_volumes;

	bool m_show_fps;
	// Contador de frames del libro SFML Game Development
	sf::Text m_fps_text;
	sf::Time m_fps_update_time;
	std::size_t m_fps_num_frames;

	// Objetos temporales, solo para pruebas
	sf::Texture back_texture;
	sf::Texture sprite_texture;
	sf::RectangleShape grid;
	sf::RectangleShape dot;
	TransitionEntity entity;
	BoxEntity box;
	sf::Sprite back;
	sf::Text m_mod_text;
};

} // namespace bmonkey

#endif // _DIRECTOR_HPP_
