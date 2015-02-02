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

#ifndef _TEXT_PATTERN_ENTITY_HPP_
#define _TEXT_PATTERN_ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "../../../defines.hpp"
#include "text_entity.hpp"
#include "../font_library.hpp"
#include "../../collection/platform.hpp"
#include "../../collection/gamelist.hpp"
#include "../../collection/game.hpp"
#include "../../../utils/parser.hpp"

namespace bmonkey{

/**
 * Entidad para dibujar textos dinámicos
 *
 * Se trata de una entidad que a partir de un patrón y los elementos necesarios,
 * dibujaa textos que dependen de estos elementos y por lo tanto pueden variar
 * durante la ejecución.
 * Los patrones reconocidos son:
 * Plataforma
 *    %p_title: Título de la plataforma
 *    %p_manufacturer: Fabricante de la plataforma
 *    %p_year: Año de fabricación
 *    %p_lists_count: Número de listas de juegos en la plataforma
 *    %p_games_count: Número total de juegos en la plataforma
 *
 * Lista
 *    %l_name: Nombre de la lista
 *    %l_filtered: Indica si está filtrada
 *    %l_games_count: Número total de juegos en la lista
 *    %l_filtered_count: Número de juegos filtrados
 *
 * Juego
 *    %g_name: Nombre de set del juego
 *    %g_title: Título del juego
 *    %g_cloneof: Nombre del set padre
 *    %g_manufacturer: Fabricante del juego
 *    %g_year: Año de lanzamiento
 *    %g_genre: Género del juego
 *    %g_players: Número de jugadores que soporta el juego
 *    %g_players_simultaneous: Indica si varios jugadores pueden jugar simultaneamente
 *    %g_rating: Puntuación del usuario para el juego
 *    %g_times_played: Número de veces que se ha jugado al juego
 *    %g_favorite: Indica si el juego está marcado como favorito
 *
 * Miscelanea
 *    %m_date: Fecha en formato: Dia_texto, Dia Mes_Texto Año
 *    %m_time: Hora en formato 24h sin minutos
 */
class TextPatternEntity : public TextEntity
{
public:
	/**
	 * Constructor de la clase
	 * @param font_library Librería de fuentes a usar por la entidad
	 */
	TextPatternEntity(FontLibrary* font_library);

	/**
	 * Destructor de la clase
	 */
	virtual ~TextPatternEntity(void);

	/**
	 * Establece la posición del pivote de la entidad
	 * @param pivot Nueva posición para el pivote de la entidad
	 */
	virtual void setPivot(Pivot pivot);

	/**
	 * Establece el color (tinte y opacidad) de la entidad
	 * @param color Nuevos valores para el tiente y la opacidad
	 */
	virtual void setColor(const sf::Color& color);

	/**
	 * Obtiene las dimensiones originales de la entidad
	 * @return Dimensiones de la entidad
	 */
	virtual sf::Vector2i getSize(void) const;

	/**
	 * Obtiene el patrón de texto a renderizar por la instancia
	 * @return Patrón de texto a renderizar
	 */
	virtual Glib::ustring getString(void) const;

	/**
	 * Establece el patrón de texto que renderizará la instancia
	 * @param text Patrón de texto a renderizar
	 */
	virtual void setString(const Glib::ustring& string);

	/**
	 * Establece la plataforma de la que extraer los patrones para el texto
	 * @param platform Nueva plataforma para los patrones
	 */
	void setPlatform(Platform* platform);

	/**
	 * Establece la lista de juegos de la que extraer los patrones para el texto
	 * @param gamelist Nueva lista de juegos para los patrones
	 */
	void setGamelist(Gamelist* gamelist);

	/**
	 * Establece el juego del que extraer los patrones para el texto
	 * @param game Nuevo juego para los patrones
	 */
	void setGame(Game* game);

protected:
	/**
	 * Realiza la actualización real de la entidad
	 * @param delta_time Tiempo transcurrido desde la última actualización
	 * @param color Color de referencia para actualizar la entidad
	 */
	virtual void updateCurrent(sf::Time delta_time, const sf::Color& color);

	/**
	 * Realiza el dibujado real de esta entidad
	 * @param target Target donde se dibujará la entidad
	 * @param states States para dibujar la entidad
	 * @param color Color a aplicar en el proceso de dibujado
	 */
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	/**
	 * Comprueba los tipos de patrones que contiene el texto patrón para mejorar
	 * la búsqueda y actulización de los tipos de patrones
	 */
	void checkPatterns(void);

	/**
	 * Actualiza las cadenas de la fecha y hora actuales
	 * @return True si actualizó algo, false en otro caso
	 */
	bool updateDateTime(void);

	/**
	 * Parsea el patrón de la entidad para generar el texto real
	 * @return Nuevo texto real a dibujar
	 */
	Glib::ustring parsePattern(void);

	Glib::ustring m_pattern;	/**< Patrón de texto a renderizar */
	Platform* m_platform;		/**< Plataforma actual a usar */
	Gamelist* m_gamelist;		/**< Lista de juegos actual a usar */
	Game* m_game;				/**< Juego actual a usar */
	bool m_has_platform;		/**< Indica si el patrón hace uso de la plataforma */
	bool m_has_gamelist;		/**< Indica si el patrón hace uso de la lista de juegos */
	bool m_has_game;			/**< Indica si el patrón hace uso del juego */
	bool m_has_miscelaneous;	/**< Indica si el patrón hace uso de la feha y hora */
	int m_last_minute;			/**< Almacena el último minuto usado */
	Glib::ustring m_date;		/**< Cadena con la conversión de la fecha */
	Glib::ustring m_time;		/**< Cadena con la conversión de la hora */
	bool m_need_parse;			/**< Indica si el patrón debe ser parseado */
	Parser m_parser;			/**< Parser interno usado por la entidad */
};

// Inclusión de los métodos inline
#include "text_pattern_entity.inl"

} // namespace bmonkey

#endif // _TEXT_PATTERN_ENTITY_HPP_
