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

#ifndef _BMONKEY_HPP_
#define _BMONKEY_HPP_

#include <glibmm/ustring.h>
#include "../defines.hpp"
#include "../utils/config.hpp"
#include "../core/collection/collection.hpp"

namespace bmonkey{

/**
 */
class BMonkeyApp
{
public:

	// Posibles comandos ejecutables por la aplicación
	enum Command
	{
		COMMAND_NONE = 0,			/**< Ningun comando */
		COMMAND_SHOW_VERSION,		/**< Mostrar versión del programa */
		COMMAND_SHOW_HELP,			/**< Muestra la ayuda del program */
		COMMAND_WINDOWED,			/**< Fuerza el modo ventana */
		COMMAND_FULLSCREEN,			/**< Fuerza el modo fullscreen */
		COMMAND_LOG_DISABLE,		/**< Deshabilita el log a fichero */
		COMMAND_LOG_ENABLE,			/**< Habilita el log a fichero */
		COMMAND_PLATFORM_ADD,		/**< Añade una nueva plataforma a la colección */
		COMMAND_PLATFORM_IMPORT,	/**< Importa una plataforma desde un dat */
		COMMAND_GAMELIST_ADD		/**< Añade una lista de jeugos nueva a una plataforma */
	};

	/**
	 * Constructor parametrizado
	 * @param working_dir Directorio de trabajo
	 */
	BMonkeyApp(const Glib::ustring& working_dir);

	/**
	 * Destructor de la clase
	 */
	virtual ~BMonkeyApp(void);

	/**
	 * Ejecuta el bucle principal de la aplicación
	 * @param argc Contador de argumentos
	 * @param argv Vector de argumentos
	 * @return -1 en caso de error, distinto de -1 en otro caso
	 */
	int run(int argc, char** argv);

private:
	/**
	 * Busca el fichero de configuración del usuario
	 * @param file Lugar donde dejar el path del fichero de configuración
	 * @return True si localizó el fichero de configuración del usuario, false
	 * en otro caso.
	 */
	bool findConfigFile(Glib::ustring& file);

	/**
	 * Parsea los parámetros pasados modificando el estado de la aplicación
	 * @param argc Contador de parámetros
	 * @param argv Vector de parámetros
	 * @return 	0 si los parámetros son correctos
	 * 			1 si los parámetros no son correctos
	 */
	int parseParams(int argc, char** argv);

	/**
	 * Ejecuta el posible comando pasado por parámetros
	 * @return -1 si se produjo algún error al ejecutar el comando
	 * 			0 si el comando se ejecutó con exito pero la app debe terminar
	 * 			1 si el comando se ejecutó con exito y la app debe continuar
	 */
	int execCommand(void);

	/**
	 * Muestra por la salida estandar un mensaje con información de uso
	 * @param program Nombre real del binario ejecutado
	 */
	void showHelp(const Glib::ustring& program);

	/**
	 * Muestra por la salida estandar un mensaje con información de la versión
	 */
	void showVersion(void);

	/**
	 * Fuerza el modo de ventana
	 */
	void setWindowed(void);

	/**
	 * Fuerza el modo de pantalla completa
	 */
	void setFullscreen(void);

	/**
	 * Desactiva el log a fichero
	 */
	void logDisable(void);

	/**
	 * Activa el log a fichero
	 */
	void logEnable(void);

	/**
	 * Añade una nueva plataforma a la colección
	 * @param name Nombre de la nueva plataforma
	 * @return 0 si se pudo realizar la operación, -1 en otro caso
	 */
	int platformAdd(const Glib::ustring& name);

	/**
	 * Importa una colección desde un fichero dat
	 * @param name Nombre de la plataforma a importar
	 * @param file Fichero dat con los juegos a importar
	 * @return 0 si se pudo realizar la operación, -1 en otro caso
	 * @note Si la plataforma no existe, se creará
	 */
	int platformImport(const Glib::ustring& name, const Glib::ustring& file);

	/**
	 * Añade una nueva lista de juegos a la plataforma dada
	 * @param platform Nombre de plataforma donde agregar la lista
	 * @param name Nombre de la nueva lista de juegos
	 * @return 0 si se pudo realizar la operación, -1 en otro caso
	 */
	int gamelistAdd(const Glib::ustring& platform, const Glib::ustring& name);

	/**
	 * Se encarga de cerrar adecuadamente los sistemas creados por el programa
	 */
	void clean(void);

	Config* m_config;				/**< Sistema de configuración para la app */
	Collection* m_collection;		/**< Colección de juegos del usuario */

	bool m_log_enabled;				/**< Indica si el log está hablitado */
	bool m_first_run;				/**< Indica si se trata del primer arranque */
	Glib::ustring m_cfg_file;		/**< Path del fichero de configuración */
	Glib::ustring m_working_dir;	/**< Path del directorio de trabajo */

	Command m_command;				/**< Comando a ejecutar */
	Glib::ustring m_param1;			/**< Primer parámetro para el comando */
	Glib::ustring m_param2;			/**< Segundo parámetro para el comando */

};

} // namespace bmonkey

#endif // _BMONKEY_HPP_
