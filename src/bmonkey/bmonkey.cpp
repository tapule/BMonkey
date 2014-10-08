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
#include "../core/datreader/dat_reader_factory.hpp"
#include "../core/bmke/control_manager.hpp"
#include "../core/bmke/sound_manager.hpp"


namespace bmonkey{

BMonkeyApp::BMonkeyApp(const Glib::ustring& working_dir):
	m_config(NULL),
	m_collection(NULL),
#ifdef ENABLE_DEBUG_MODE
	m_log_enabled(true),
#else
	m_log_enabled(false),
#endif
	m_first_run(true),
	m_working_dir(working_dir),
	m_command(COMMAND_NONE),
	m_rotation(NONE)
{
	assert(!m_working_dir.empty());
}

BMonkeyApp::~BMonkeyApp(void)
{
};

int BMonkeyApp::run(int argc, char** argv)
{
	int ret;
	Glib::ustring collection_dir, tmp_dir;

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
	// Si no existe la entrada del estado del log, creamos una nueva
	if (!m_config->getKey(BMONKEY_CFG_GLOBAL, "log_enabled", m_log_enabled))
	{
		m_config->setKey(BMONKEY_CFG_GLOBAL, "log_enabled", m_log_enabled);
	}

	// Inicializamos el sistema de log
	LOG_DEBUG("BMonkey: Initializing log...");
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
	collection_dir = Glib::build_filename(tmp_dir, USER_COLLECTION_DIR);
	if (!utils::checkOrCreateDir(collection_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	tmp_dir = Glib::build_filename(collection_dir, PLATFORM_BACKGROUNDS_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	tmp_dir = Glib::build_filename(collection_dir, PLATFORM_SNAPS_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	tmp_dir = Glib::build_filename(collection_dir, PLATFORM_WHEELS_DIR);
	if (!utils::checkOrCreateDir(tmp_dir))
	{
		clean();
		return EXIT_FAILURE;
	}
	tmp_dir = Glib::build_filename(collection_dir, PLATFORM_VIDEOS_DIR);
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

	// Parseamos los parámetros introducidos por linea de comandos
	LOG_DEBUG("BMonkey: Parsing parameters...");
	ret = parseParams(argc, argv);
	if (ret == 1)
	{
		clean();
		return EXIT_FAILURE;
	}
	// Ejecutamos el posible comando
	ret = execCommand();
	if (ret < 1)
	{
		LOG_INFO("Shutting down BMonkey...");
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

	/*******************************************************
	 * Bucle principal de la aplicación
	*******************************************************/
	float fixed_fps = 60.f;
	sf::Time fixed_fps_time = sf::Time::Zero;
    sf::Time elapsed_time = sf::Time::Zero;
    sf::Clock clock;
    ControlManager control_manager(m_window);
    ControlManager::Event event;
    SoundManager sound_manager;

    LOG_INFO("BMonkey: Initializing renderer...");
 	screenInit();
 	LOG_INFO("BMonkey: Loading keymap...");
 	if (!control_manager.load(Glib::build_filename(m_working_dir, BMONKEY_KEYMAP_FILE)))
 	{
 		control_manager.registerDefaultControls();
 	}
 	LOG_INFO("BMonkey: Loading sounds...");

 	sound_manager.loadSound(SoundManager::SELECT, "sounds/gs1.ogg");
 	sound_manager.loadSound(SoundManager::BACK, "sounds/gs2.ogg");
 	sound_manager.loadSound(SoundManager::PREVIOUS, "sounds/gs3.ogg");
 	sound_manager.loadSound(SoundManager::NEXT, "sounds/gs4.ogg");
 	sound_manager.loadSound(SoundManager::UP, "sounds/gs5.ogg");
 	sound_manager.loadSound(SoundManager::DOWN, "sounds/gs6.ogg");
 	sound_manager.loadSound(SoundManager::LEFT, "sounds/gs7.ogg");
 	sound_manager.loadSound(SoundManager::RIGHT, "sounds/gs8.ogg");
 	//sound_manager.loadSound(SoundManager::JUMP_BACKWARD, "sounds/gs9.ogg");
 	sound_manager.loadSound(SoundManager::JUMP_FORWARD, "sounds/gs10.ogg");
 	sound_manager.loadSound(SoundManager::MENU_OPEN, "sounds/gs11.ogg");
 	sound_manager.loadSound(SoundManager::ERROR, "sounds/gs12.ogg");
 	sound_manager.loadSound(SoundManager::SPECIAL, "sounds/gs13.ogg");
 	sound_manager.openMusic("sounds/mus.ogg");
 	sound_manager.setMusicVolume(75.f);
 	sound_manager.setSoundVolume(75.f);

    control_manager.enableEvent(ControlManager::SELECT);
    control_manager.enableEvent(ControlManager::BACK);
    control_manager.enableEvent(ControlManager::PLATFORM_PREVIOUS);
    control_manager.enableEvent(ControlManager::PLATFORM_NEXT);
    control_manager.enableEvent(ControlManager::GAME_PREVIOUS);
    control_manager.enableEvent(ControlManager::GAME_NEXT);
    control_manager.enableEvent(ControlManager::EXIT_MENU);
    control_manager.enableEvent(ControlManager::SWITCH_ROTATION);


 	// Obtenemos el tiempo para las actualizaciones fijas
	if (!m_config->getKey(BMONKEY_CFG_CORE, "fixed_framerate", fixed_fps))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "fixed_framerate", fixed_fps);
	}
	if (fixed_fps == 0)
	{
		fixed_fps = 60.f;
	}
	fixed_fps_time = sf::seconds(1.f/fixed_fps);

    while (m_window.isOpen())
    {
    	elapsed_time += clock.restart();
        while (elapsed_time > fixed_fps_time)
        {
        	elapsed_time -= fixed_fps_time;

            // Esto es lo mismo que el handleInput();
			while (control_manager.poolEvent(event))
			{

				switch (event)
				{
				case ControlManager::EXIT:
					m_window.close();
					break;
				case ControlManager::UNFOCUSED:
					sound_manager.pauseMusic();
					sound_manager.stopAllSound();
					break;
				case ControlManager::FOCUSED:
					sound_manager.playMusic();
					break;
				case ControlManager::SELECT:
					sound_manager.playSound(SoundManager::SELECT);
					break;
				case ControlManager::BACK:
					sound_manager.playSound(static_cast<SoundManager::Effect>(rand() % 13));
					break;
				case ControlManager::PLATFORM_PREVIOUS:
					sound_manager.setSoundVolume(sound_manager.getSoundVolume() - 5);
					LOG_DEBUG("snd vol: " << sound_manager.getSoundVolume());
					break;
				case ControlManager::PLATFORM_NEXT:
					sound_manager.setSoundVolume(sound_manager.getSoundVolume() + 5);
					LOG_DEBUG("snd vol: " << sound_manager.getSoundVolume());
					break;
				case ControlManager::GAME_PREVIOUS:
					sound_manager.setMusicVolume(sound_manager.getMusicVolume() + 5);
					LOG_DEBUG("mus vol: " << sound_manager.getMusicVolume());
					break;
				case ControlManager::GAME_NEXT:
					sound_manager.setMusicVolume(sound_manager.getMusicVolume() - 5);
					LOG_DEBUG("mus vol: " << sound_manager.getMusicVolume());
					break;
				case ControlManager::EXIT_MENU:
					sound_manager.stopMusic();
					break;
				case ControlManager::SWITCH_ROTATION:
					sound_manager.playMusic();
					break;
				}
			}
            //update(fixed_fps_time);
        }
        draw();
    }

    control_manager.save();

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

	m_command = COMMAND_NONE;
	m_param1.clear();
	m_param2.clear();

	// Comenzamos en 1 ya que argv[0] es el nombre del programa ejecutado
	i = 1;
	while (i < argc)
	{
		// -v muestra la versión del programa y termina
		if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version") == 0))
		{
			m_command = COMMAND_SHOW_VERSION;
			return 0;
		}
		// -h muestra la ayuda del programa y termina
		else if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
		{
			m_command = COMMAND_SHOW_HELP;
			m_param1 = argv[0];
			return 0;
		}
		// -w fuerza el modo ventana
		else if ((strcmp(argv[i], "-w") == 0) || (strcmp(argv[i], "--windowed") == 0))
		{
			m_command = COMMAND_WINDOWED;
			return 0;
		}
		// -f fuerza el modo fullscreen
		else if ((strcmp(argv[i], "-f") == 0) || (strcmp(argv[i], "--fullscreen") == 0))
		{
			m_command = COMMAND_FULLSCREEN;
			return 0;
		}
		// -ld desactiva el log
		else if ((strcmp(argv[i], "-ld") == 0) || (strcmp(argv[i], "--log-disable") == 0))
		{
			m_command = COMMAND_LOG_DISABLE;
			return 0;
		}
		// -le activa el log
		else if ((strcmp(argv[i], "-le") == 0) || (strcmp(argv[i], "--log-enable") == 0))
		{
			m_command = COMMAND_LOG_ENABLE;
			return 0;
		}
		// -pa añade una plataforma a la colección
		else if ((strcmp(argv[i], "-pa") == 0) || (strcmp(argv[i], "--platform-add") == 0))
		{
			m_command = COMMAND_PLATFORM_ADD;
			// Necesitamos un parámetros más con el nombre de la plataforma
			if (i < argc - 1)
			{
				m_param1 = argv[i + 1];
			}
			else
			{
				std::cout << "BMonkey: --platform-add wrong params:" << std::endl
						<< "Usage: " << argv[0] << " --platform-add platform_name" << std::endl;
				return 1;
			}
			return 0;
		}
		// -pi importa una plataforma desde un fichero dat
		else if ((strcmp(argv[i], "-pi") == 0) || (strcmp(argv[i], "--platform-import") == 0))
		{
			m_command = COMMAND_PLATFORM_IMPORT;
			// Necesitamos dos parámetros más, la plataforma y el fichero dat
			if (i < argc - 2)
			{
				m_param1 = argv[i + 1];
				m_param2 = argv[i + 2];
			}
			else
			{
				std::cout << "BMonkey: --platform-import wrong params:" << std::endl
						<< "Usage: " << argv[0] << " --platform-import platform_name File" << std::endl;
				return 1;
			}
			return 0;
		}
		// -ga añade una gamelist a una plataforma dada
		else if ((strcmp(argv[i], "-ga") == 0) || (strcmp(argv[i], "--gamelist-add") == 0))
		{
			m_command = COMMAND_GAMELIST_ADD;
			// Necesitamos dos parámetros más, la plataforma y el nombre de la lista
			if (i < argc - 2)
			{
				m_param1 = argv[i + 1];
				m_param2 = argv[i + 2];
			}
			else
			{
				std::cout << "BMonkey: --gamelist-add wrong params:" << std::endl
						<< "Usage: " << argv[0] << " --gamelist-add platform_name gamelist-name" << std::endl;
				return 1;
			}
			return 0;
		}
		else{
			DEBUG("BMonkey: Unknown option \"" << argv[i] << "\"");
			std::cout << "Unknown option \"" << argv[i] << "\"" << std::endl;
			return 1;
		}
		++i;
	}
	return 0;
}

int BMonkeyApp::execCommand(void)
{
	int ret;

	// Ejecución de los posibles comandos
	switch (m_command)
	{
	case COMMAND_SHOW_VERSION:
		showVersion();
		ret = 0;
		break;
	case COMMAND_SHOW_HELP:
		showHelp(m_param1);
		ret = 0;
		break;
	case COMMAND_WINDOWED:
		setWindowed();
		ret = 1;
		break;
	case COMMAND_FULLSCREEN:
		setFullscreen();
		ret = 1;
		break;
	case COMMAND_LOG_DISABLE:
		logDisable();
		ret = 1;
		break;
	case COMMAND_LOG_ENABLE:
		logEnable();
		ret = 1;
		break;
	case COMMAND_PLATFORM_ADD:
		ret = platformAdd(m_param1);
		break;
	case COMMAND_PLATFORM_IMPORT:
		ret = platformImport(m_param1, m_param2);
		break;
	case COMMAND_GAMELIST_ADD:
		ret = gamelistAdd(m_param1, m_param2);
		break;
	default:
		ret = 1;
		break;
	}
	return ret;
}

void BMonkeyApp::showHelp(const Glib::ustring& program)
{
	showVersion();
	std::cout << "Usage: " << program << " [Options] [Platform Name] [File / Gamelist Name]" << std::endl
			  << std::endl
			  << "Available options:" << std::endl
			  << "  -v, --version            Display BMonkey version information and exit" << std::endl
			  << "  -h, --help               Display this help message and exit" << std::endl
			  << "  -w, --windowed           Force windowed mode" << std::endl
			  << "  -f, --fullscreen         Force full-screen mode" << std::endl
			  << "  -ld, --log-disable       Disable logging" << std::endl
			  << "  -le, --log-enable        Enable logging" << std::endl
			  << "  -pa, --platform-add      Force full-screen mode" << std::endl
			  << "  -pi, --platform-import   Disable logging" << std::endl
			  << "  -ga, --gamelist-add      Enable logging" << std::endl;
}

void BMonkeyApp::showVersion(void)
{
	std::cout << "Bmonkey Frontend v" << PACKAGE_VERSION << std::endl
			  << "Copyright (C) 2014 Juan Ángel Moreno Fernández" << std::endl;
}

void BMonkeyApp::setWindowed(void)
{
	LOG_DEBUG("BMonkey: Setting windowed mode...");
	m_config->setKey(BMONKEY_CFG_SCREEN, "fullscreen", false);
}

void BMonkeyApp::setFullscreen(void)
{
	LOG_DEBUG("BMonkey: Setting fullscreen mode...");
	m_config->setKey(BMONKEY_CFG_SCREEN, "fullscreen", true);
}

void BMonkeyApp::logDisable(void)
{
	if (m_log_enabled)
	{
		LOG_DEBUG("BMonkey: Disabling logging...");
		m_log_enabled = false;
		m_config->setKey(BMONKEY_CFG_GLOBAL, "log_enabled", m_log_enabled);
		LOG_CLOSE();
	}
}

void BMonkeyApp::logEnable(void)
{
	if (!m_log_enabled)
	{
		LOG_DEBUG("BMonkey: Enabling logging...");
		m_log_enabled = true;
		m_config->setKey(BMONKEY_CFG_GLOBAL, "log_enabled", m_log_enabled);
		LOG_OPEN(Glib::build_filename(m_working_dir, BMONKEY_LOG_FILE));
	}
}

int BMonkeyApp::platformAdd(const Glib::ustring& name)
{
	Platform* platform = NULL;

	m_collection = new Collection(m_working_dir);
	m_collection->loadConfig();
	platform = m_collection->platformCreate(name);
	if (!platform)
	{
		LOG_DEBUG("BMonkey: Can't create platform \"" << name << "\"");
		std::cout << "Can't create platform \"" << name << "\"" << std::endl;
		delete m_collection;
		return -1;
	}
	// Cargamos la configuración y juegos por si la plataforma ya existe
	platform->loadConfig();
	platform->loadGames();
	platform->saveGames();
	platform->saveConfig();
	m_collection->saveConfig();
	delete m_collection;

	return 0;
}

int BMonkeyApp::platformImport(const Glib::ustring& name, const Glib::ustring& file)
{
	DatReader* dat = NULL;
	std::vector<DatSet> sets;
	std::vector<DatSet>::iterator iter;
	Platform* platform = NULL;
	Gamelist* list = NULL;
	Game* game = NULL;
	int total = 0;

	// Obtenemos un lector de dat para el fichero
	dat = DatReaderFactory::getDatReader(file);
	if (!dat)
	{
		std::cout << "Dat reader not found for file \"" << file << "\"" <<  std::endl;
		return -1;
	}
	// Mostramos la info del dat y sus sets
	std::cout << "Dat type: " << dat->getType() <<  std::endl;
	if (!dat->read(sets))
	{
		std::cout << "Error reading sets" <<  std::endl;
		delete dat;
		return -1;
	}
	std::cout << "Total dat sets: " << sets.size() <<  std::endl;
	std::cout << "-------------------------------------" <<  std::endl;

	m_collection = new Collection(m_working_dir);
	m_collection->loadConfig();
	platform = m_collection->platformCreate(name);
	if (!platform)
	{
		LOG_DEBUG("BMonkey: Can't create platform \"" << name << "\"");
		std::cout << "Can't create platform \"" << name << "\"" << std::endl;
		delete m_collection;
		delete dat;
		return -1;
	}
	// Cargamos la configuración y juegos por si la plataforma ya existe
	platform->loadConfig();
	// Obtenemos lista master y agremgamos los juegos
	list = platform->gamelistGet();
	// Procesamos todos los sets del dat
	for (iter = sets.begin(); iter != sets.end(); ++iter)
	{
		if (!iter->is_bios)
		{
			std::cout << "Adding set: " << iter->name << " / \"" << iter->description << "\"" << std::endl;
			game = new Game(platform->getDir());
			game->name = iter->name;
			game->title = iter->description;
			game->cloneof = iter->clone_of;
			game->crc = iter->crc;
			game->manufacturer = iter->manufacturer;
			game->year = iter->year;
			game->genre = iter->genre;
			game->players = iter->players;
			list->gameAdd(game);
			++total;
		}
	}
	std::cout << "-------------------------------------" <<  std::endl;
	std::cout << "New sets: " << total << std::endl;

	// Remapeamos las listas de juegos si existen
	platform->loadGamelists();
	platform->saveGamelists();
	platform->saveGames();
	platform->saveConfig();
	m_collection->saveConfig();
	delete m_collection;
	delete dat;

	return 0;
}

int BMonkeyApp::gamelistAdd(const Glib::ustring& platform, const Glib::ustring& name)
{
	int ret = 0;
	Platform* plt = NULL;

	m_collection = new Collection(m_working_dir);
	m_collection->loadConfig();
	plt = m_collection->platformGet(platform);
	if (!plt)
	{
		ret = -1;
		LOG_DEBUG("BMonkey: Platform \"" << platform << "\" does not exist");
		std::cout << "Platform \"" << platform << "\" does not exist" << std::endl;
	}
	else
	{
		plt->loadConfig();
		plt->loadGames();
		plt->loadGamelists();
		if (!plt->gamelistCreate(name))
		{
			ret = -1;
			LOG_DEBUG("BMonkey: Can't create gamelist \"" << name << "\"");
			std::cout << "Can't create gamelist \"" << name << "\"" << std::endl;
		}
		else
		{
			plt->saveGamelists();
		}
	}
	m_collection->saveConfig();
	delete m_collection;

	return ret;

}

void BMonkeyApp::screenInit(void)
{
	bool fullscreen = false;
	unsigned int width = 800;
	unsigned int height = 600;
	unsigned int bpp = 32;
	Glib::ustring rotation_txt = "none";
	Rotation rotation = NONE;
	sf::ContextSettings ctx_settings;
	unsigned int antialiasing_level = 0;
	bool vsync = false;
	unsigned int fps_limit = 0;
	float joystick_threshold = 75.f;
	//float mouse_threshold;
	unsigned int style;
	sf::View view;

	// Comprobamos las variables de configuración y fijamos valores por defecto
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "fullscreen", fullscreen))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "fullscreen", fullscreen);
	}
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "width", width))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "width", width);
		m_config->setKey(BMONKEY_CFG_SCREEN, "heigth", height);
	}
	else
	{
		if (!m_config->getKey(BMONKEY_CFG_SCREEN, "heigth", height))
		{
			m_config->setKey(BMONKEY_CFG_SCREEN, "heigth", height);
		}
	}
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "bpp", bpp))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "bpp", bpp);
	}
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "rotation", rotation_txt))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "rotation", rotation_txt);
	}
	else
	{
		rotation_txt = rotation_txt.lowercase();
		if (rotation_txt == "left")
		{
			rotation = LEFT;
		}
		else if (rotation_txt == "right")
		{
			rotation = RIGHT;
		}
		else if (rotation_txt == "inverted")
		{
			rotation = INVERTED;
		}
	}
	if (!m_config->getKey(BMONKEY_CFG_CORE, "antialiasing_level", antialiasing_level))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "antialiasing_level", antialiasing_level);
	}
	if (!m_config->getKey(BMONKEY_CFG_CORE, "vertical_sync", vsync))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "vertical_sync", vsync);
	}
	if (!m_config->getKey(BMONKEY_CFG_CORE, "framerate_limit", fps_limit))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "framerate_limit", fps_limit);
	}
	if (!m_config->getKey(BMONKEY_CFG_CORE, "joystick_threshold", joystick_threshold))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "joystick_threshold", joystick_threshold);
	}

	if (fullscreen)
	{
		style = sf::Style::Fullscreen;
	}
	else
	{
		style = sf::Style::Titlebar | sf::Style::Close;
	}
	ctx_settings.antialiasingLevel = antialiasing_level;
	m_window.create(sf::VideoMode(width, height, bpp), "BMonkey 0.1", style, ctx_settings);
	m_window.setVerticalSyncEnabled(vsync);
	// Si vsync está habilitado, el limite fps puede dar problemas
	m_window.setFramerateLimit(fps_limit);
	screenRotate(rotation);

	if (joystick_threshold != 0)
	{
		m_window.setJoystickThreshold(joystick_threshold);
	}
}

void BMonkeyApp::screenRotate(const Rotation rotation)
{
	unsigned int width;
	unsigned int height;
	sf::View view;
	std::string rotation_txt;

	// Asumimos que previamente se etableción una resolución adecuada
	m_config->getKey(BMONKEY_CFG_SCREEN, "width", width);
	m_config->getKey(BMONKEY_CFG_SCREEN, "heigth", height);

	view = m_window.getDefaultView();
	switch(rotation)
	{
	case RIGHT:
		view.setRotation(90.f);
		view.setCenter(height/2.f, width/2.f);
		rotation_txt = "right";
		break;
	case INVERTED:
		view.setRotation(180.f);
		view.setCenter(width/2.f, height/2.f);
		rotation_txt = "inverted";
		break;
	case LEFT:
		view.setRotation(-90.f);
		view.setCenter(height/2.f, width/2.f);
		rotation_txt = "left";
		break;
	default:
		view.setRotation(0.f);
		view.setCenter(width/2.f, height/2.f);
		rotation_txt = "none";
		break;
	}
	m_window.setView(view);
	// Guardamos nueva configuración de rotación
	m_rotation = rotation;
	m_config->setKey(BMONKEY_CFG_SCREEN, "rotation", rotation_txt);
}

void BMonkeyApp::screenSwitchRotation(void)
{
	int rotation;

	rotation = m_rotation;
	if (rotation == LEFT)
	{
		rotation = NONE;
	}
	else
	{
		++rotation;
	}
	screenRotate(static_cast<Rotation>(rotation));
}

void BMonkeyApp::draw(void)
{
	sf::Texture texture;
    texture.loadFromFile("v.png");
    sf::Sprite sprite(texture);

	m_window.clear();
	m_window.draw(sprite);
	m_window.display();
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
