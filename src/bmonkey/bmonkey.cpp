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

#include "bmonkey.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <glibmm/miscutils.h>
#include <glibmm/fileutils.h>
#include "../utils/utils.hpp"


namespace bmonkey{

BMonkeyApp::BMonkeyApp(const Glib::ustring& working_dir):
	m_config(NULL),
#ifdef ENABLE_DEBUG_MODE
	m_log_enabled(true),
#else
	m_log_enabled(false),
#endif
	m_first_run(true),
	m_working_dir(working_dir)
{
	assert(!m_working_dir.empty());
}

BMonkeyApp::~BMonkeyApp(void)
{
};

int BMonkeyApp::run(int argc, char** argv)
{
	int ret;
	Glib::ustring main_dir, tmp_dir;

	// Iniciamos el sistema de configuración
	LOG_DEBUG("BMonkey: Initializing Config system...");
	m_config = new Config();
	m_config->setRoot(BMONKEY_CFG_ROOT, BMONKEY_CFG_VERSION);
	// Buscamos el fichero de configuración y lo cargamos
	if (findConfigFile(m_cfg_file))
	{
		m_config->load(m_cfg_file);
	}
	// Almacenamos el directorio de trabajo actual en la configuración
	m_config->setKey(BMONKEY_CFG_GLOBAL, "current_working_dir", m_working_dir);

	// Parseamos los parámetros introducidos por linea de comandos
	LOG_DEBUG("BMonkey: Parsing parameters...");
	ret = parseParams(argc, argv);
	if (ret < 1)
	{
		clean();
		if (ret == 0)
		{
			return EXIT_SUCCESS;
		}
		else
		{
			return EXIT_FAILURE;
		}
	}

	// Inicializamos el sistema de log
	LOG_DEBUG("BMonkey: Initializing log...");
	if (!m_config->getKey(BMONKEY_CFG_GLOBAL, "log_enabled", m_log_enabled))
	{
		m_config->setKey(BMONKEY_CFG_GLOBAL, "log_enabled", m_log_enabled);
	}
	if (m_log_enabled)
	{
		LOG_DEBUG("BMonkey: Log enabled.");
		LOG_OPEN(Glib::build_filename(m_working_dir, BMONKEY_LOG_FILE));
		// Mensajes de inicialización
		LOG_INFO("Initializing BMonkey...");
		LOG_INFO("BMonkey: Version " << PACKAGE_VERSION);
		LOG_INFO("BMonkey: Working dir " << m_working_dir);
	}
	else
	{
		LOG_DEBUG("BMonkey: Log disabled.");
	}

	// Comprobamos el directorio de datos del usuario (library)
	LOG_INFO("BMonkey: Checking user library directory...");
	tmp_dir = Glib::build_filename(m_working_dir, USER_LIBRARY_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	main_dir = Glib::build_filename(tmp_dir, USER_MAIN_DIR);
	if (!utils::checkOrCreateDir(main_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	tmp_dir = Glib::build_filename(main_dir, COLLECTION_BACKGROUNDS_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	tmp_dir = Glib::build_filename(main_dir, COLLECTION_SNAPS_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	tmp_dir = Glib::build_filename(main_dir, COLLECTION_WHEELS_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	tmp_dir = Glib::build_filename(main_dir, COLLECTION_VIDEOS_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}

	// Comprobamos el directorio de themes del usuario (themes)
	LOG_INFO("BMonkey: Checking user themes directory...");
	tmp_dir = Glib::build_filename(m_working_dir, USER_THEMES_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}



	/*******************************************************
	 * Bucle principal de la aplicación
	*******************************************************/
	LOG_INFO("BMonkey: Running main_sec...");


	/*******************************************************/

	// Limpiamos los sistemas creados
	LOG_INFO("Shutting down BMonkey...");
	clean();

	return EXIT_SUCCESS;
}

bool BMonkeyApp::findConfigFile(Glib::ustring& file)
{
	Glib::ustring cfg_file;

	// Construimos el path al fichero de configuración
	cfg_file = Glib::build_filename(m_working_dir, BMONKEY_CFG_FILE);
	if (!Glib::file_test(cfg_file, Glib::FILE_TEST_EXISTS))
	{
		DEBUG("BMonkey: Configuration file \""<< cfg_file << "\" not found");
		return false;
	}
	else
	{
		DEBUG("BMonkey: Configuration file found \"" << cfg_file << "\"");
		file = cfg_file;
		return true;
	}
}

int BMonkeyApp::parseParams(int argc, char** argv)
{
	int i;

	// Comenzamos en 1 ya que argv[0] es el nombre del programa ejecutado
	i = 1;
	while (i < argc)
	{
		// -v muestra su info y termina la ejecución de forma controlada
		if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version") == 0))
		{
			showVersion();
			return 0;
		}
		// -h muestra su info y terminan la ejecución de forma controlada
		else if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
		{
			showHelp(argv[0]);
			return 0;
		}
		// -l desactiva el log
		else if ((strcmp(argv[i], "-l") == 0) || (strcmp(argv[i], "--disable-log") == 0))
		{
			DEBUG("BMonkey: Disabling logging...");
			m_config->setKey(BMONKEY_CFG_GLOBAL, "log_enabled", FALSE);
			return 1;
		}
		// -L activa el log
		else if ((strcmp(argv[i], "-L") == 0) || (strcmp(argv[i], "--enable-log") == 0))
		{
			DEBUG("BMonkey: Enabling logging...");
			m_config->setKey(BMONKEY_CFG_GLOBAL, "log_enabled", TRUE);
			return 1;
		}
		else if ((strcmp(argv[i], "-w") == 0) || (strcmp(argv[i], "--windowed") == 0))
		{
			DEBUG("BMonkey: Disabling fullscreen...");
			m_config->setKey(BMONKEY_CFG_UI, "fullscreen_mode", FALSE);
		}
		else if ((strcmp(argv[i], "-f") == 0) || (strcmp(argv[i], "--fullscreen") == 0))
		{
			DEBUG("BMonkey: Enabling fullscreen...");
			m_config->setKey(BMONKEY_CFG_UI, "fullscreen_mode", TRUE);
		}
		else
		{
			DEBUG("BMonkey: Unknown option \"" << argv[i] << "\"");
			std::cout << "Unknown option \"" << argv[i] << "\"" << std::endl;
			return -1;
		}
		++i;
	}
	return 1;
}

void BMonkeyApp::showHelp(const Glib::ustring& program)
{
	showVersion();
	std::cout << "Usage: " << program << " [Options]" << std::endl
			  << std::endl
			  << "Available options:" << std::endl
			  << "  -v, --version            Display BMonkey version information and exit" << std::endl
			  << "  -h, --help               Display this help message and exit" << std::endl
			  << "  -l, --disable-log        Disable logging" << std::endl
			  << "  -L, --enable-log         Enable logging" << std::endl
			  << "  -w, --windowed           Force windowed mode" << std::endl
			  << "  -f, --fullscreen         Force full-screen mode" << std::endl;
}

void BMonkeyApp::showVersion(void)
{
	std::cout << "Bmonkey Frontend v" << PACKAGE_VERSION << std::endl
			  << "Copyright (C) 2014 Juan Ángel Moreno Fernández" << std::endl;
}

void BMonkeyApp::clean(void)
{
	// Guardamos la configuración
	if(m_config)
	{
		LOG_INFO("BMonkey: Shutting down Config system...");
		// Almacenamos antes el último directorio de trabajo
		m_config->setKey(BMONKEY_CFG_GLOBAL, "last_working_dir", m_working_dir);
		m_cfg_file = Glib::build_filename(m_working_dir, BMONKEY_CFG_FILE);
		m_config->save(m_cfg_file);
		delete m_config;
		m_config = NULL;
	}

	LOG_CLOSE();
}

} // namespace bmonkey
