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

#ifndef _DEFINES_HPP_
#define _DEFINES_HPP_

#ifdef HAVE_CONFIG_H
	#include <config.h>
#else
	// Defines por defecto
	#define ENABLE_DEBUG_MODE
	#define PACKAGE_NAME			"BMonkey"
	#define PACKAGE_VERSION			"0.0.1"
//	#define PACKAGE_CODENAME		 "\"bmk\""
	#define PACKAGE_WEBSITE			"http:/bmonkey.sf.net"
	#define PACKAGE_DATA_DIR		"."
#endif

// CHECKME: Este defines solo se utiliza en wip, para release hay que quitarlo
// Activa el modo de ejecución local.
// El modo de ejecución local implica que todo el procesamiento se realizará
// desde el directorio donde reside el binario.
#define ENABLE_LOCAL_MODE

// En win siempre se usará el modo local
#ifdef OS_WIN
	#define ENABLE_LOCAL_MODE
#endif


#ifndef ENABLE_DEBUG_MODE
	#define NDEBUG
#endif

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include "utils/i18n.hpp"
#include "utils/os_detect.hpp"
#include "utils/debug.hpp"
#include "utils/log.hpp"


// Directorios de trabajo en función del tipo de ejecución. La versión win
// siempre se compilará con modo local activado.
#ifdef ENABLE_LOCAL_MODE
	#ifdef OS_POSIX
		#define BMONKEY_DATA_DIR			"data"
		#define BMONKEY_ICON_DIR			BMONKEY_DATA_DIR
		#define BMONKEY_FONTS_DIR			BMONKEY_DATA_DIR"/fonts"
		#define BMONKEY_THEMES_DIR			BMONKEY_DATA_DIR"/themes"
	#else
		#define BMONKEY_DATA_DIR			"data"
		#define BMONKEY_ICON_DIR			BMONKEY_DATA_DIR
		#define BMONKEY_FONTS_DIR			BMONKEY_DATA_DIR"\\fonts"
		#define BMONKEY_THEMES_DIR			BMONKEY_DATA_DIR"\\themes"
	#endif
#else
	#define BMONKEY_DATA_DIR				PACKAGE_DATA_DIR"/bmonkey"
	#define BMONKEY_ICON_DIR				PACKAGE_DATA_DIR"/icons/hicolor/scalable/apps"
	#define BMONKEY_FONTS_DIR				BMONKEY_DATA_DIR"/fonts"
	#define BMONKEY_THEMES_DIR				BMONKEY_DATA_DIR"/themes"
#endif

// Estructura de directorios para datos del usuario
// Toda la estructura se montará a partir del directory de trabajo del usuario
#define USER_LIBRARY_DIR				"library"
#define USER_COLLECTION_DIR				"collection"		// library/collection
#define USER_THEMES_DIR					"themes"
#define USER_SCREENSHOT_DIR				"screenshots"

// Estructura de directorios para las plataformas
// Toda la estructura se montará a partir del directorio de la plataforma
#define PLATFORM_ROMS_DIR				"roms"
#define PLATFORM_GAMELISTS_DIR			"gamelists"
#define PLATFORM_BACKGROUNDS_DIR		"backgrounds"
#define PLATFORM_SNAPS_DIR				"snaps"
#define PLATFORM_WHEELS_DIR				"wheels"
#define PLATFORM_VIDEOS_DIR				"videos"

// Directorio de trabajo por defecto
#define BMONKEY_DEFAULT_DIR				".bmonkey"

// Ficheros manejados por bmonkey
#define BMONKEY_ICON_FILE				"bmonkey.png"
#define BMONKEY_CFG_FILE				"bmonkey.xml"
#define BMONKEY_KEYMAP_FILE				"keymap.xml"
#define BMONKEY_COLLECTION_FILE			"collection.xml"
#define BMONKEY_PLATFORM_FILE			"config.xml"
#define BMONKEY_GAMES_FILE				"games.xml"
#define BMONKEY_LOG_FILE				"bmonkey.log"
#define BMONKEY_DEFAULT_FONT_FILE		"FreeSans.ttf"
#define BMONKEY_DEFAULT_THEME			"default"

// Root, versión y grupos para el fichero de configuración de bmonkey
#define BMONKEY_CFG_ROOT				"bmonkeycfg"
#define BMONKEY_CFG_VERSION				"0.1"
#define BMONKEY_CFG_GLOBAL				"global"
#define BMONKEY_CFG_SCREEN				"screen"
#define BMONKEY_CFG_SOUND				"sound"
#define BMONKEY_CFG_CORE				"core"
#define BMONKEY_CFG_SCREENSAVER			"screensaver"
#define BMONKEY_CFG_MENUS				"menus"



#endif // _DEFINES_HPP_
