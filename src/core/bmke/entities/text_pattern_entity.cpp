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

#include "text_pattern_entity.hpp"
#include <cassert>
#include <ctime>
#include "../../../utils/utils.hpp"

namespace bmonkey{

// Tipo enumerado para identificar los tokens
enum
{
	// Tokens para las plataformas
	TK_P_TITLE,
	TK_P_MANUFACTURER,
	TK_P_YEAR,
	TK_P_LISTS_COUNT,
	TK_P_GAMES_COUNT,
	// Tokens para las listas de juegos
	TK_L_NAME,
	TK_L_FILTERED,
	TK_L_GAMES_COUNT,
	TK_L_FILTERED_COUNT,
	// Tokens para los juegos
	TK_G_NAME,
	TK_G_TITLE,
	TK_G_CLONEOF,
	TK_G_MANUFACTURER,
	TK_G_YEAR,
	TK_G_GENRE,
	TK_G_PLAYERS,
	TK_G_PLAYERS_SIMULTANEOUS,
	TK_G_RATING,
	TK_G_TIMES_PLAYED,
	TK_G_FAVORITE,
	// Tokens miscelanea
	TK_M_DATE,
	TK_M_TIME,
	// Contador de palabras reservadas
	NUM_TK_WORDS
};

TextPatternEntity::TextPatternEntity(FontLibrary* font_library):
	TextEntity(font_library),
	m_platform(nullptr),
	m_gamelist(nullptr),
	m_game(nullptr),
	m_has_platform(false),
	m_has_gamelist(false),
	m_has_game(false),
	m_has_miscelaneous(false),
	m_last_minute(0),
	m_need_parse(false)
{
	std::vector<ReservedWord> words =
	{
		{TK_P_TITLE, "%p_title"},
		{TK_P_MANUFACTURER, "%p_manufacturer"},
		{TK_P_YEAR, "%p_year"},
		{TK_P_LISTS_COUNT, "%p_lists_count"},
		{TK_P_GAMES_COUNT, "%p_games_count"},

		{TK_L_NAME, "%l_name"},
		{TK_L_FILTERED, "%l_filtered"},
		{TK_L_GAMES_COUNT, "%l_games_count"},
		{TK_L_FILTERED_COUNT, "%l_filtered_count"},

		{TK_G_NAME, "%g_name"},
		{TK_G_TITLE, "%g_title"},
		{TK_G_CLONEOF, "%g_cloneof"},
		{TK_G_MANUFACTURER, "%g_manufacturer"},
		{TK_G_YEAR, "%g_year"},
		{TK_G_GENRE, "%g_genre"},
		{TK_G_PLAYERS, "%g_players"},
		{TK_G_PLAYERS_SIMULTANEOUS, "%g_players_simultaneous"},
		{TK_G_RATING, "%g_rating"},
		{TK_G_TIMES_PLAYED, "%g_times_played"},
		{TK_G_FAVORITE, "%g_favorite"},

		{TK_M_DATE, "%m_date"},
		{TK_M_TIME, "%m_time"},
	};
	// Configuramos el parser
	m_parser.setStringDetection(false);
	m_parser.setNumberDetection(false);
	m_parser.setDelimiters(" \n\r\t\v\f,.;:\"()[]<>{}");
	m_parser.setReservedWords(words);
}

TextPatternEntity::~TextPatternEntity(void)
{
}

void TextPatternEntity::setPlatform(Platform* platform)
{
	if (m_platform != platform)
	{
		m_platform = platform;
		// Si el patrón tiene plataforma, forzamos el parseo de la cadena
		if (m_has_platform)
		{
			m_need_parse = true;
		}
	}
}

void TextPatternEntity::setGamelist(Gamelist* gamelist)
{
	if (m_gamelist != gamelist)
	{
		m_gamelist = gamelist;
		// Si el patrón tiene listas, forzamos el parseo de la cadena
		if (m_has_gamelist)
		{
			m_need_parse = true;
		}
	}
}

void TextPatternEntity::setGame(Game* game)
{
	if (m_game != game)
	{
		m_game = game;
		// Si el patrón tiene juegos, forzamos el parseo de la cadena
		if (m_has_game)
		{
			m_need_parse = true;
		}
	}
}

void TextPatternEntity::updateCurrent(sf::Time delta_time, const sf::Color& color)
{
	// Comprobamos si tenemos que actualizar fecha y hora para esta entidad
	if (m_has_miscelaneous)
	{
		// Solo forzamos el parseo de la cadena si cambió algo de la fecha-hora
		m_need_parse = updateDateTime() ? true : m_need_parse;
	}
	if (m_need_parse)
	{
		TextEntity::setString(parsePattern());
		m_need_parse = false;
	}
}

void TextPatternEntity::checkPatterns(void)
{
	Token token;

	m_has_platform = false;
	m_has_gamelist = false;
	m_has_game = false;
	m_has_miscelaneous = false;

	m_parser.reset();
	while (m_parser.hasMoreTokens())
	{
		token = m_parser.nextToken();
		if (token.type <= TK_P_GAMES_COUNT)
		{
			m_has_platform = true;
		}
		else if (token.type >= TK_L_NAME && token.type <= TK_L_FILTERED_COUNT)
		{
			m_has_gamelist = true;
		}
		else if (token.type >= TK_G_NAME && token.type <= TK_G_FAVORITE)
		{
			m_has_game = true;
		}
		else if (token.type >= TK_M_DATE && token.type <= TK_M_TIME)
		{
			m_has_miscelaneous = true;
		}
	}
}

bool TextPatternEntity::updateDateTime(void)
{
	// Almacen para conversión de los textos
	static char buff[30];
	time_t raw_time;
	struct tm * time_info;

	time(&raw_time);
	time_info = localtime(&raw_time);
	// Solamente actualizamos si ha transcurrido un minuto
	if (time_info->tm_min != m_last_minute)
	{
		strftime(buff, 30, "%A, %d ", time_info);
		buff[0] = toupper(buff[0]);
		m_date = buff;
		strftime(buff, 30, "%B %Y", time_info);
		buff[0] = toupper(buff[0]);
		m_date += buff;
		strftime(buff, 30, "%H:%M", time_info);
		m_time = buff;
		m_last_minute = time_info->tm_min;
		return true;
	}
	return false;
}

Glib::ustring TextPatternEntity::parsePattern(void)
{
	Glib::ustring text;
	Glib::ustring next;
	Token token;

	m_parser.reset();
	while (m_parser.hasMoreTokens())
	{
		// Copiamos los delimitadores encontrados
		text += m_parser.lastDelimiterString();
		token = m_parser.nextToken();
		next = token.string;

		// Comprobamos si hay que procesar la plataforma
		if (token.string.find("%p_", 0) == 0)
		{
			// Como es un patrón, inicialmente lo limpiamos para no poner patrones inválidos
			next.clear();
			if (m_platform)
			{
				switch (token.type)
				{
				case TK_P_TITLE:
					next = m_platform->getTitle();
					break;
				case TK_P_MANUFACTURER:
					next = m_platform->getManufacturer();
					break;
				case TK_P_YEAR:
					next = m_platform->getYear();
					break;
				case TK_P_LISTS_COUNT:
					next = utils::toStr(m_platform->gamelistCount());
					break;
				case TK_P_GAMES_COUNT:
					next = utils::toStr(m_platform->gamelistGet()->gameCount());
					break;
				}
			}
		}
		// Comprobamos si hay que procesar la lista de juegos
		if (token.string.find("%l_", 0) == 0)
		{
			next.clear();
			if (m_gamelist)
			{
				switch (token.type)
				{
				case TK_L_NAME:
					next = m_gamelist->getName().empty() ? _("Master") : m_gamelist->getName();
					break;
				case TK_L_FILTERED:
					next = m_gamelist->isFiltered() ? _("Yes") : _("Not");
					break;
				case TK_L_GAMES_COUNT:
					next = utils::toStr(m_gamelist->gameCount());
					break;
				case TK_L_FILTERED_COUNT:
					next = utils::toStr(m_gamelist->gameCountFiltered());
					break;
				}
			}
		}
		// Comprobamos si hay que procesar el juego
		if (token.string.find("%g_", 0) == 0)
		{
			next.clear();
			if (m_game)
			{
				switch (token.type)
				{
				case TK_G_NAME:
					next = m_game->name;
					break;
				case TK_G_TITLE:
					next = m_game->title;
					break;
				case TK_G_CLONEOF:
					next = m_game->cloneof;
					break;
				case TK_G_MANUFACTURER:
					next = m_game->manufacturer;
					break;
				case TK_G_YEAR:
					next = m_game->year;
					break;
				case TK_G_GENRE:
					next = m_game->genre;
					break;
				case TK_G_PLAYERS:
					next = utils::toStr(m_game->players);
					break;
				case TK_G_PLAYERS_SIMULTANEOUS:
					next = m_game->simultaneous ? _("Yes") : _("Not");
					break;
				case TK_G_RATING:
					next = utils::toStr(m_game->rating);
					break;
				case TK_G_TIMES_PLAYED:
					next = utils::toStr(m_game->times_played);
					break;
				case TK_G_FAVORITE:
					next = m_game->favorite ? _("Yes") : _("Not");
					break;
				}
			}
		}
		if (token.string.find("%m_", 0) == 0)
		{
			next.clear();
			switch (token.type)
			{
			case TK_M_DATE:
				next = m_date;
				break;
			case TK_M_TIME:
				next = m_time;
				break;
			}
		}
		text += next;
	}
	// Copiamos los delimitadores finales si hubieran
	text += m_parser.lastDelimiterString();
	return text;
}

} // namespace bmonkey
