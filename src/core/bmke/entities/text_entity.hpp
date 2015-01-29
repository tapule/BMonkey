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

#ifndef _TEXT_ENTITY_HPP_
#define _TEXT_ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "../../../defines.hpp"
#include "../entity.hpp"
#include "../font_library.hpp"

namespace bmonkey{

/**
 * Entidad para dibujar texto estático
 *
 * Se trata de una entidad base para dibujar textos estáticos, es decir, textos
 * que no variarán durante la ejecución.
 * El texto está compuesto de texto frontal, borde y sombra.
 * Tanto el borde como la sombra se pueden desactivar para reducir la carga
 * de dibujado de la entidad.
 */
class TextEntity : public Entity
{
public:
	// Posibles estilos para el texto
	enum Style
	{
		REGULAR = 0,
        BOLD = 1,
        ITALIC = 2,
        UNDERLINED = 4,
        STRIKETHROUGH = 8
	};

	/**
	 * Constructor de la clase
	 * @param font_library Librería de fuentes a usar por la entidad
	 */
	TextEntity(FontLibrary* font_library);

	/**
	 * Destructor de la clase
	 */
	virtual ~TextEntity(void);

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
	virtual sf::Vector2f getSize(void) const;

	/**
	 * Obtiene la fuente usada por la entidad
	 * @return Fuente usada por la entidad
	 */
	sf::Font* getFont(void);

	/**
	 * Establece la fuente que usará la entidad
	 * @param font Nueva fuente a usar por la entidad
	 * @note La entidad solicitará la descarga de la fuente a la librería de
	 * fuentes, cuando ya no sea necesaria.
	 */
	void setFont(sf::Font* font);

	/**
	 * Obtiene el texto a renderizar por la instancia
	 * @return Texto a renderizar
	 */
	Glib::ustring getString(void) const;

	/**
	 * Establece el texto que renderizará la instancia
	 * @param text Texto a renderizar
	 */
	virtual void setString(const Glib::ustring& string);

	/**
	 * Obtiene el tamaño base de los caracteres del texo en pixeles
	 * @return Tamaño base de los caracteres en pixeles
	 */
	unsigned int getCharacterSize(void) const;

	/**
	 * Establece el tamaño base de los caracteres del texo en pixeles
	 * @param size Nuevo tamaño base para los caracteres
	 */
	void setCharacterSize(const unsigned int size);

	/**
	 * Obtiene el estilo aplicado al texto
	 * @return Estilo aplicado
	 */
	Style getStyle(void);

	/**
	 * Establece el tipo de estilo que se aplicará al texto
	 * @param style Nuevo estilo para aplicar al texto
	 */
	void setStyle(const Style& style);

	/**
	 * Obtiene el color del texto
	 * @return Color del texto
	 */
	const sf::Color& getTextColor(void);

	/**
	 * Establece el color del texto
	 * @param color Nuevo color para el texto
	 */
	void setTextColor(const sf::Color& color);

	/**
	 * Obtiene la longitud máxima permitida para el texto
	 * @return Máxima longitud permitida para el texto
	 */
	unsigned int getMaxLength(void);

	/**
	 * Establece la longitud máxima del texto
	 * @param length Nueva longitud máxima para el texto
	 * @note 0 indicará que no hay longitud máxima.
	 */
	void setMaxLength(const unsigned int length);

	/**
	 * Indica si se activo el forzado de mayúsculas
	 * @return Estado del forzado de mayúsculas
	 */
	bool getForceUppercase(void);

	/**
	 * Establece si es necesario forzar las mayúsculas
	 * @param uppercase Nuevo valor para el forzado de mayúsculas
	 */
	void setForceUppercase(const bool uppercase);

	/**
	 * Indica si el renderizado del outline está habilitado
	 * @return True si el outline está habilitado, false en otro caso
	 */
	bool getOutlineEnabled(void) const;

	/**
	 * Establece si el renderizado del outline está habilitado
	 * @param enabled Nuevo valor para el flag de renderizaod del outline
	 */
	void setOutlineEnabled(const bool enabled);

	/**
	 * Obtiene el color para el outline del texto
	 * @return Color del outline del texto
	 */
	const sf::Color& getOutlineColor(void);

	/**
	 * Establece el color para el outline del texto
	 * @param color Nuevo color para el outline
	 */
	void setOutlineColor(const sf::Color& color);

	/**
	 * Indica si el renderizado del sombreado está habilitado
	 * @return True si el sombreado está habilitado, false en otro caso
	 */
	bool getShadowEnabled(void) const;

	/**
	 * Establece si el renderizado del sombreado está habilitado
	 * @param enabled Nuevo valor para el flag de renderizado del sombreado
	 */
	void setShadowEnabled(const bool enabled);

	/**
	 * Obtiene el color de la sombra aplicada al texto
	 * @return Color de la sombra aplicada al texto
	 */
	const sf::Color& getShadowColor(void);

	/**
	 * Establece el color de la sombra aplicada al texto
	 * @param color Nuevo color para la sombra del texto
	 */
	void setShadowColor(const sf::Color& color);

	/**
	 * Obtiene el offset en pixeles aplicado a la sombra del texto
	 * @return Offset en pixeles de la sombra del texto
	 */
	sf::Vector2i getShadowOffset(void) const;

	/**
	 * Establece el offset en pixeles aplicado a la sombra del texto
	 * @param ox Nuevo offset sobre el eje x
	 * @param oy Nuevo offset sobre el eje y
	 */
	void setShadowOffset(const int ox, const int oy);

	/**
	 * Establece el offset en pixeles aplicado a la sombra del texto
	 * @param offset Nuevo offset para la sombra del texto
	 */
	void setShadowOffset(const sf::Vector2i& offset);

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

	/**
	 * Convierte una cadena Glib::ustring a sf::String
	 * @param ustring Cadena a convertir
	 * @return Nueva cadena convertida
	 */
	sf::String fromUstring(const Glib::ustring& ustring);

private:
	FontLibrary* m_font_library;		/**< Librería de fuentes a usar por la entidad */
	sf::Font* m_font;					/**< SFML Font usada */
	Glib::ustring m_string;				/**< Cadena de texto a renderizar */
	unsigned int m_character_size;		/**< Tamaño base de los caracteres en pixeles */
	Style m_style;						/**< Estilo aplicado al texto */
	sf::Color m_text_color;				/**< Color del texto */
	unsigned int m_max_length;			/**< Longitud máxima permitida para el texto */
	bool m_force_uppercase;				/**< Indica si hay que forzar mayúsculas */
	bool m_outline_enabled;				/**< Indica si el renderizado del outline está habilitado */
	sf::Color m_outline_color;			/**< Color del outline, ignora alpha */
	bool m_shadow_enabled;				/**< Indica si el renderizado de la sombra está habilitado */
	sf::Color m_shadow_color;			/**< Color de la sombra del texto */
	sf::Vector2i m_shadow_offset;		/**< Offsets de la sombra en pixeles */
	sf::Vector2f m_shadow_position;		/**< Posición de la sombra */
	sf::Text m_text;					/**< Texto para cálculos internos */
};

// Inclusión de los métodos inline
#include "text_entity.inl"

} // namespace bmonkey

#endif // _TEXT_ENTITY_HPP_
