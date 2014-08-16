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

#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

#include <glibmm/ustring.h>
#include <unordered_map>
#include <vector>
#include "../item.hpp"
#include "../../defines.hpp"
#include "gamelist.hpp"

namespace bmonkey{

/**
 * Mantiene la información de una plataforma.
 *
 * Una plataforma, además de ser la abstracción de una Consola/Arcade/Simulador
 * etc., actua como contenedor de sus listas de juegos.
 * Posee una lista de juegos master donde se almacenan todos los juegos de la
 * plataforma y cero o más listas de juegos genéricas con selecciones de juegos
 * del usuario.
 */
class Platform: public Item
{
public:
	/**
	 * Constructor parametrizado
	 * @param name Nombre de la plataforma
	 * @param library_dir Directorio base de la librería de plataformas del sistema
	 */
	Platform(const Glib::ustring& name, const Glib::ustring& library_dir);

	/**
	 * Destructor de la clase
	 */
	virtual ~Platform(void);

	/**
	 * Obtiene el directorio de trabajo o directorio base de la Plataforma
	 * @return Referencia al directorio de trabajo de la plataforma
	 */
	Glib::ustring& getDir(void)
	{
		return m_dir;
	}

	/**
	 * Obtiene la siguiente plataforma enlazado
	 * @return Siguiente plataforma enlazada
	 */
	Platform* getNext(void)
	{
		return m_next;
	}

	/**
	 * Establece la siguiente plataforma enlazado
	 * @param next Siguiente plataforma a enlazar
	 */
	void setNext(Platform* next)
	{
		m_next = next;
	}

	/**
	 * Obtiene la plataforma previa enlazada
	 * @return Plataforma previa
	 */
	Platform* getPrev(void)
	{
		return m_prev;
	}

	/**
	 * Establece la plataforma previa enlazada
	 * @param prev Plataforma previa a enlazar
	 */
	void setPrev(Platform* prev)
	{
		m_prev = prev;
	}

	/**
	 * Obtiene el título de la plataforma
	 * @return Título de la plataforma
	 */
	Glib::ustring getTitle(void)
	{
		return m_title;
	}

	/**
	 * Estable el título de la plataforma
	 * @param title Título nombre para la plataforma
	 */
	void setTitle(const Glib::ustring& title)
	{
		m_title = title;
	}

	/**
	 * Obtiene el fabricante de la plataforma
	 * @return Fabricante de la plataforma
	 */
	Glib::ustring getManufacturer(void)
	{
		return m_manufacturer;
	}

	/**
	 * Estable fabricante de la plataforma
	 * @param manufacturer Nuevo fabricante de la plataforma
	 */
	void setManufacturer(const Glib::ustring& manufacturer)
	{
		m_manufacturer = manufacturer;
	}

	/**
	 * Obtiene el año de lanzamiento de la plataforma
	 * @return Año de lanzamiento de la plataforma
	 */
	Glib::ustring getYear(void)
	{
		return m_year;
	}

	/**
	 * Estable año de lanzamiento de la plataforma
	 * @param year Nuevo año de lanzamiento de la plataforma
	 */
	void setYear(const Glib::ustring& year)
	{
		m_year = year;
	}

	/**
	 * Obtiene el directorio de roms de la plataforma
	 * @return Directorio de roms de la plataforma
	 */
	Glib::ustring getRomsDir(void)
	{
		return m_roms_dir;
	}

	/**
	 * Establece el directorio de roms de la plataforma
	 * @param dir Nuevo directorio de roms para la plataforma
	 */
	void setRomsDir(const Glib::ustring& dir);

	/**
	 * Obtiene la extensión reconocible para las roms de la plataforma
	 * @return Extensión de las roms de la plataforma
	 */
	Glib::ustring getRomsExtension(void)
	{
		return m_roms_extension;
	}

	/**
	 * Estable la extensión reconocible para las roms de la plataforma
	 * @param extension Nueva extensión para las roms de la plataforma
	 */
	void setRomExtension(const Glib::ustring& extension)
	{
		m_roms_extension = extension;
	}

	/**
	 * Obtiene el path del binario del emulador para la plataforma
	 * @return Path del binario de la plataforma
	 */
	Glib::ustring getEmulatorBinary(void)
	{
		return m_emu_binary;
	}

	/**
	 * Estable el path del binario del emulador de la plataforma
	 * @param binary Path del binario del emulador
	 */
	void setEmulatorBinary(const Glib::ustring& binary)
	{
		m_emu_binary = binary;
	}

	/**
	 * Obtiene los parámetros que se pasarán al emulador
	 * @return Parámetros para el emulador
	 */
	Glib::ustring getEmulatorParams(void)
	{
		return m_emu_params;
	}

	/**
	 * Estable los parámetros que se pasarán al emulador
	 * @param params Parámetros para la emulación
	 */
	void setEmulatorParams(const Glib::ustring& params)
	{
		m_emu_params = params;
	}

	/**
	 * Obtiene el comando a ejecutar antes que la emulación
	 * @return Comando a ejecutar antes de la emulación
	 */
	Glib::ustring getPreCommand(void)
	{
		return m_pre_command;
	}

	/**
	 * Estable el comando a ejecutar antes que la emulación
	 * @param command Comando a ejecutar antes de la emulación
	 */
	void setPreCommand(const Glib::ustring& command)
	{
		m_pre_command = command;
	}

	/**
	 * Obtiene el comando a ejecutar despues de la emulación
	 * @return Comando a ejecutar despues de la emulación
	 */
	Glib::ustring getPostCommand(void)
	{
		return m_post_command;
	}

	/**
	 * Estable el comando a ejecutar despues de la emulación
	 * @param command Comando a ejecutar despues de la emulación
	 */
	void setPostCommand(const Glib::ustring& command)
	{
		m_post_command = command;
	}

	/**
	 * Obtiene el directorio desde el que se lanzará la emulación
	 * @return Path del directorio desde el que lanzar la emulación
	 */
	Glib::ustring getRunDir(void)
	{
		return m_run_dir;
	}

	/**
	 * Estable el directorio desde el que lanzar la emulación
	 * @param dir Path del directorio desde el que lanzar la emulación
	 */
	void setRunDir(const Glib::ustring& dir)
	{
		m_run_dir = dir;
	}

	/**
	 * Carga el fichero de configuración de la plataforma
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool loadConfig(void);

	/**
	 * Carga el listado de juegos de la plataforma
	 * @return true si se pudo realizar la operación, falso en otro caso
	 * @note No se permiten juegos duplicados por set name. Los duplicados se
	 * descartan en la carga
	 */
	bool loadGames(void);

	/**
	 * Carga las listas de juegos de la plataforma
	 * @return true si se pudo realizar la operación, falso en otro caso
	 * @note Los juegos duplicados o inexistentes en la lista master, son
	 * descartados
	 */
	bool loadGamelists(void);

	/**
	 * Guarda la configuración de la plataforma en su fichero correspondiente
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveConfig(void);

	/**
	 * Guarda los juegos de la plataforma en su fichero
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveGames(void);

	/**
	 * Guarda las listas de juegos de la plataforma
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveGamelists(void);

	/**
	 * Elimina el juego indicado de la lista de juegos indicada
	 * @param name Nombre del juego a eliminar
	 * @param list Lista de juegos de la que eliminar
	 * @return true si se pudo realizar la operación, false en otro caso
	 * @note Si la lista es la master, se eliminará de todas las listas
	 */
	bool gameDelete(const Glib::ustring& name, Gamelist* list);

	/**
	 * Obtiene el vector con los nombres de las listas de juegos de la plataforma
	 * @return Vector de nombres de las listas de juegos
	 * @note Este vector no incluye información sobre la lista master
	 */
	std::vector<Glib::ustring>& getGamelists(void)
	{
		return m_lists_names;
	}

	/**
	 * Obtiene la lista master de la plataforma.
	 * @return Lista master de la plataforma
	 */
	Gamelist* gamelistGet(void)
	{
		return m_master;
	}

	/**
	 * Obtiene una lista de juegos mediante su nombre
	 * @param name Nombre de la lista de juegos buscada
	 * @return Lista de juegos buscada o null si no existe
	 */
	Gamelist* gamelistGet(const Glib::ustring& name);

	/**
	 * Crea una nueva lista de juegos del usuario en la plataforma
	 * @param name Nombre de la nueva lista de juegos
	 * @return Nueva lista creada o null si no se pudo crear
	 * @note No se permiten nombres de listas duplicados
	 */
	Gamelist* gamelistCreate(const Glib::ustring& name);

	/**
	 * Obtiene el número de listas de juegos disponibles en la plataforma
	 * @return Número de listas de juegos de la plataforma
	 * @note No se cuenta la lista master, sino las listas del usuario
	 */
	int gamelistCount(void)
	{
		return m_lists_names.size();
	}

	// Implementación de Item
	/**
	 * Obtiene el nombre de la plataforma
	 * @return Cadena de texto con el nombre de la plataforma
	 */
	Glib::ustring itemName(void)
	{
		return m_name;
	}

	/**
	 * Obtiene el titulo de la plataforma
	 * @return Cadena de texto con el titulo de la plataforma
	 */
	Glib::ustring itemTitle(void)
	{
		return m_title;
	}

	/**
	 * Obtiene el directorio donde se almacenan los recursos de la plataforma
	 * @return Directorio de recursos de la plataforma
	 */
	Glib::ustring itemResourcesDir(void)
	{
		return m_resources_dir;
	}

private:
	/**
	 * Se encarga de limpiar los almacenes internos de los datos
	 */
	void clean(void);

	Glib::ustring m_library_dir;	/**< Directorio base de la librería del sistema */
	Glib::ustring m_dir;			/**< Directorio de trabajo de la plataforma */
	Glib::ustring m_resources_dir;	/**< Directorio donde residen los recursos de la plataforma */

	Platform* m_next;				/**< Siguiente plataforma en la colección */
	Platform* m_prev;				/**< Plataforma anterior en la colección */

	Glib::ustring m_name;			/**< Nombre de la plataforma */
	Glib::ustring m_title;			/**< Título de la plataforma */
	Glib::ustring m_manufacturer;	/**< Fabricante de la plataforma */
	Glib::ustring m_year;			/**< Año de lanzamiento */

	Glib::ustring m_roms_dir;		/**< Directorio de roms de la plataforma */
	Glib::ustring m_roms_extension;	/**< Extensión de las roms de la plataforma */

	Glib::ustring m_emu_binary;		/**< Path del binario del emulador */
	Glib::ustring m_emu_params;		/**< Parámetros a pasar al emulador */
	Glib::ustring m_pre_command;	/**< Comando a ejecutar como paso previo */
	Glib::ustring m_post_command;	/**< Comando a ejecutar como paso posterior */
	Glib::ustring m_run_dir;		/**< Directorio lanzamiento de la emulación */

	Gamelist* m_master;
	std::unordered_map<std::string, Gamelist* > m_lists_map;	/**< Mapa de listas para acceso rápido por nombre */
	std::vector<Glib::ustring> m_lists_names;	/**< Vector con los nombres de las listas */
};

} // namespace bmonkey

#endif // _PLATFORM_HPP_
