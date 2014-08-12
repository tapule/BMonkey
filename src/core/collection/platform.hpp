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

#ifndef _COLLECTION_HPP_
#define _COLLECTION_HPP_

#include <glibmm/ustring.h>
#include <unordered_map>
#include <vector>
#include "gamelist.hpp"
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Mantiene la información de una colección.
 *
 * Una colecci
 */
class Platform
{
public:
	/**
	 * Constructor parametrizado
	 * @param working_dir Directorio de trabajo
	 */
	Platform(const Glib::ustring& working_dir){}

	/**
	 * Destructor de la clase
	 */
	virtual ~Platform(void){}

	Gamelist* gamelistGet(void) {}

	Gamelist* gamelistGet(const Glib::ustring& name) {}

	std::vector<Glib::ustring>& getGamelists() {}


	inline Glib::ustring getDir(void){}

	/**
	 * Obtiene el directorio de trabajo de la colección
	 * @return Cadena de texto con el path del directorio de trabajo
	 */
	inline Glib::ustring getWorkingDir(void){}

	/**
	 * Estable el path del directorio de trabajo de la colección
	 * @param working_dir Nuevo path para el directorio de trabajo
	 */
	inline void setWorkingDir(const Glib::ustring& working_dir){}

	/**
	 * Obtiene el nombre de la colección
	 * @return Cadena de texto con el nombre de la colección
	 */
	inline Glib::ustring getName(void){}

	/**
	 * Estable el nombre de la colección
	 * @param name Nuevo nombre para la colección
	 */
	inline void setName(const Glib::ustring& name){}

	/**
	 * Obtiene el fabricante de la plataforma vinculada a la colección
	 * @return Fabricante de la plataforma
	 */
	inline Glib::ustring getManufacturer(void){}

	/**
	 * Estable fabricante de la plataforma vinculada a la colección
	 * @param manufacturer Nuevo fabricante de la plataforma
	 */
	inline void setManufacturer(const Glib::ustring& manufacturer){}

	/**
	 * Obtiene el año de lanzamiento de la plataforma vinculada a la colección
	 * @return Año de lanzamiento de la plataforma
	 */
	inline Glib::ustring getYear(void){}

	/**
	 * Estable año de lanzamiento de la plataforma vinculada a la colección
	 * @param year Nuevo año de lanzamiento de la plataforma
	 */
	inline void setYear(const Glib::ustring& year){}

	/**
	 * Obtiene el directorio de roms de la colección
	 * @return Directorio de roms de la colección
	 */
	inline Glib::ustring getRomsDir(void){}

	/**
	 * Establece el directorio de roms de la colección
	 * @param dir Nuevo directorio de roms para la colección
	 */
	inline void setRomsDir(const Glib::ustring& dir){}

	/**
	 * Obtiene la extensión reconocible para las roms de la colección
	 * @return Extensión de las roms de la colección
	 */
	inline Glib::ustring getRomsExtension(void){}

	/**
	 * Estable la extensión reconocible para las roms de la colección
	 * @param extension Nueva extensión para las roms de la colección
	 */
	inline void setRomExtension(const Glib::ustring& extension){}

	/**
	 * Obtiene el path del binario del emulador para la colección
	 * @return Path del binario de la colección
	 */
	inline Glib::ustring getEmulatorBinary(void){}

	/**
	 * Estable el path del binario del emulador de la colección
	 * @param binary Path del binario del emulador
	 */
	inline void setEmulatorBinary(const Glib::ustring& binary){}

	/**
	 * Obtiene los parámetros que se pasarán al emulador
	 * @return Parámetros para el emulador
	 */
	inline Glib::ustring getEmulatorParams(void){}

	/**
	 * Estable los parámetros que se pasarán al emulador
	 * @param params Parámetros para la emulación
	 */
	inline void setEmulatorParams(const Glib::ustring& params){}

	/**
	 * Obtiene el comando a ejecutar antes que la emulación
	 * @return Comando a ejecutar antes de la emulación
	 */
	inline Glib::ustring getPreCommand(void){}

	/**
	 * Estable el comando a ejecutar antes que la emulación
	 * @param command Comando a ejecutar antes de la emulación
	 */
	inline void setPreCommand(const Glib::ustring& command){}

	/**
	 * Obtiene el comando a ejecutar despues de la emulación
	 * @return Comando a ejecutar despues de la emulación
	 */
	inline Glib::ustring getPostCommand(void){}

	/**
	 * Estable el comando a ejecutar despues de la emulación
	 * @param command Comando a ejecutar despues de la emulación
	 */
	inline void setPostCommand(const Glib::ustring& command){}

	/**
	 * Obtiene el directorio desde el que se lanzará la emulación
	 * @return Path del directorio desde el que lanzar la emulación
	 */
	inline Glib::ustring getRunDir(void){}

	/**
	 * Estable el directorio desde el que lanzar la emulación
	 * @param dir Path del directorio desde el que lanzar la emulación
	 */
	inline void setRunDir(const Glib::ustring& dir){}

	/**
	 * Carga el fichero de configuración de la colección
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool loadConfig(void){}

	/**
	 * Carga el listado de juegos de la colección
	 * @return true si se pudo realizar la operación, falso en otro caso
	 * @note No se permiten juegos duplicados por set name. Los duplicados se
	 * descartan en la carga
	 */
	bool loadGames(void){}

	/**
	 * Carga las listas de juegos de la colección
	 * @return true si se pudo realizar la operación, falso en otro caso
	 * @note Los juegos duplicados o inexistentes en la lista master, son
	 * descartados
	 */
	bool loadGamelists(void){}

	/**
	 * Guarda la configuración de la colección en su fichero correspondiente
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveConfig(void){}

	/**
	 * Guarda los juegos de la colección en su fichero
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveGames(void){}

	/**
	 * Guarda las listas de juegos de la colección
	 * @return true si se pudo realizar la operación, falso en otro caso
	 */
	bool saveGamelists(void){}

	/**
	 * Obtiene una lista de juegos a partir de su identificador
	 * @param id Identificador de la lista de juegos requerida
	 * @return Lista buscada o Null si no se puede localizar
	 * @note La lista master no se puede obtener con este método
	 */
	Gamelist* gamelistGet(int id){}

	/**
	 * Obtiene la lista master de la colección
	 * @return Lista master de la colección o Null si no se puede localizar
	 */
	Gamelist* gamelistGetMaster(void){}

	/**
	 * Busca una lista de juegos mediiante su nombre
	 * @param name Nombre de la lista de juegos buscada
	 * @return Lista buscada o Null si no se pudo localizar
	 */
	Gamelist* gamelistFind(const Glib::ustring& name){}

	/**
	 * Crea una nueva lista en la colección con un nombre dado
	 * @return Identificador de la nueva lista o -1 si no se pudo crear
	 */
	int gamelistCreate(const Glib::ustring& name){}

	/**
	 * Elimina la lista de juegos indicada por su id
	 * @param id Identificador de la lista de juegos a eliminar
	 * @return true si se pudo realizar la operación, false en otro caso
	 * @note La lista master no se puede eliminar con este método
	 */
	bool gamelistDelete(int id){}

	/**
	 * Obtiene el id de la primera lista de juegos de la colección
	 * @return Identificador de la lista o -1 si no se pudo localizar
	 */
	int gamelistFirst(void){}

	/**
	 * Obtiene el id de la siguiente lista a una dada por su id
	 * @param id Identificado de la lista de la que obtener su siguiente
	 * @return id de la siguiente lista o -1 si no se pudo localizar
	 */
	int gamelistNext(int id){}

	/**
	 * Obtiene el id de la lista anterior a una dada por su id
	 * @param id Identificado de la lista de la que obtener la anterior
	 * @return id de la lista anterior o -1 si no se pudo localizar
	 */
	int gamelistPrevious(int id){}

	/**
	 * Obtiene el id de la última lista de la colección
	 * @return Identificador de la última lista o -1 si no se pudo localizar
	 */
	int gamelistLast(void){}

	/**
	 * Obtiene el número de listas de juegos disponibles en la colección
	 * @return Número de listas de juegos de la colección
	 */
	inline int gamelistCount(void){}

private:
	Glib::ustring m_working_dir;	/**< Directorio de trabajo de la colección */
	Glib::ustring m_name;			/**< Nombre de la colección */
	Glib::ustring m_manufacturer;	/**< Fabricante de la colección */
	Glib::ustring m_year;			/**< Año de lanzamiento */

	Glib::ustring m_roms_dir;		/**< Directorio de roms de la colección */
	Glib::ustring m_roms_extension;	/**< Extensión de las roms de la colección */

	Glib::ustring m_emu_binary;		/**< Path del binario del emulador */
	Glib::ustring m_emu_params;		/**< Parámetros a pasar al emulador */
	Glib::ustring m_pre_command;	/**< Comando a ejecutar como paso previo */
	Glib::ustring m_post_command;	/**< Comando a ejecutar como paso posterior */
	Glib::ustring m_run_dir;		/**< Directorio lanzamiento de la emulación */
};

} // namespace bmonkey

#endif // _COLLECTION_HPP_
