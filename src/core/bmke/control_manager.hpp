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

#ifndef _CONTROL_MANAGER_HPP_
#define _CONTROL_MANAGER_HPP_

#include <SFML/Window.hpp>
#include <glibmm/ustring.h>
#include <vector>
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Gestiona los eventos de entrada generados por el usuario.
 *
 * Se encarga de mapear los comandos generados por el usuario sobre el teclado,
 * Joystick, Mouse, etc, a eventos del frontend.
 * Dispone de dos set de controles configurables para cada posible evento más
 * una tecla modificadora o Alt Key para poder aumentar el uso de las diferentes
 * teclas, botones, etc.
 * Permite habilitar o deshabilitar los eventos.
 * Se define como singleton, de forma que solamente tendrémos una instancia
 * durante toda la ejecución.
 */
class ControlManager
{
public:

	// Máximo número de control sets configurables
	static const unsigned char MAX_CONTROL_SETS;

	// Posibles eventos generados por BMonkey
	enum Event
	{
		SELECT = 0,				/**< Selecciona el elemento actual */
		BACK,					/**< Vuelve atrás */
		PLATFORM_PREVIOUS,		/**< Selecciona la plataforma anterior */
		PLATFORM_NEXT,			/**< Selecciona la plataforma siguiente */
		GAME_PREVIOUS,			/**< Selecciona el juego anterior */
		GAME_NEXT,				/**< Selecciona el juego siguiente */
		GAME_LETTER_PREVIOUS,	/**< Retrocede a la letra anterior del nombre del juego */
		GAME_LETTER_NEXT,		/**< Avanza a la letra siguiente del nombre del juego */
		GAME_JUMP_BACKWARD,		/**< Salta n juegos atrás */
		GAME_JUMP_FORWARD,		/**< Salta n juegos adelante */
		MENU_UP,				/**< Selecciona el item encima del actual */
		MENU_DOWN,				/**< Selecciona el item debajo del actual */
		MENU_LEFT,				/**< Selecciona el item a la izquierda del actual */
		MENU_RIGHT,				/**< Selecciona el item a la derecha del actual */
		EXIT_MENU,				/**< Abre el menú "Exit" */
		LISTS_MENU,				/**< Abre el menú "Lists" */
		VOLUME_MENU,			/**< Abre el menú "Volume" */
		FILTERS_MENU,			/**< Abre el menú "Filters" */
		GAME_MENU,				/**< Abre el menú "Game" */
		CONTROLS_MENU,			/**< Abre el menú "Controls" */
		SWITCH_ROTATION,		/**< Cambia la rotación de la pantalla */
		// Estos son eventos del sistema, no se pueden desactivar
		OTHER,					/**< Otro evento desconocido */
		EXIT,					/**< Evento de finalización del programa */
		FOCUSED,				/**< La ventana gana el foco */
		UNFOCUSED				/**< La ventana pierde el foco */
	};

protected:
	/**
	 * Constructor de la clase
	 */
	ControlManager(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~ControlManager(void);

	/**
	 * Constructor de copia anulado para reforzar el singleton
	 */
	ControlManager(ControlManager const&);

	/**
	 * Operador de copia anulado para reforzar el singleton
	 */
	ControlManager& operator=(ControlManager const&);

public:

	/**
	 * Obtiene la instancia única del manager
	 * @return Instancia única del manager
	 */
	static ControlManager* getInstance(void);

	/**
	 * Establece la ventana que será manejada por el manager
	 * @param window Ventana a manejar por el manager
	 */
	void setWindow(sf::Window& window);

	/**
	 * Carga la configuración de los eventos desde un fichero XML
	 * @param file Path del fichero XML con la configuración
	 * @return true Si se pudo realizar la carga, false en otro caso.
	 */
	bool load(const Glib::ustring& file);

	/**
	 * Guarda la configuración de los eventos en un fichero especificado
	 * @param file Path del fichero donde guardar la configuración
	 * @return true si se pudo guardar la configuración, false en otro caso
	 */
	bool save(const Glib::ustring& file);

	/**
	 * Guarda la configuración de eventos en el mismo fichero del que se cargó
	 * @return true si se pudo guardar la configuración, false en otro caso
	 */
	bool save(void);

	/**
	 * Obtiene el siguiente evento de la cola de eventos
	 * @param event Nuevo evento leído de la cola de eventos
	 * @return True si se leyó algun evento, false en otro caso
	 */
	bool poolEvent(Event& event);

	/**
	 * Habilita un evento indicado
	 * @param event Evento a habilitar
	 * @note El evento OTHER no puede ser modificado
	 */
	void enableEvent(const Event event);

	/**
	 * Deshabilita un evento indicado
	 * @param event Evento a deshabilitar
	 * @note El evento OTHER no puede ser modificado
	 */
	void disableEvent(const Event event);

	/**
	 * Deshabilita todos los eventos excepto OTHER que no puede ser modificado
	 */
	void disableAllEvent(void);

	/**
	 * Registra para un evento de un control set, el comando dado
	 * @param event Evento a registrar
	 * @param set Control set en el que registrar el evento
	 * @param command Comando a registrar
	 */
	void registerEvent(const Event event, const unsigned char set, const std::string& command);

	/**
	 * Obtiene el estado actual de los eventos del sistema
	 * @return Vector con todos los estados de los eventos del sistema
	 */
	std::vector<bool> getEventsStatus(void) const;

	/**
	 * Establece los estados de los eventos del sistema
	 * @param status Nuevos estados para los eventos
	 */
	void setEventsStatus(const std::vector<bool>& status);

	/**
	 * Indica si se debe ignorar la Alt key
	 * @param ignore Nuevo valor para ignorar la Alt key
	 */
	void ignoreAltKey(const bool ignore);

	/**
	 * Obtiene la Alt key configurada para el control set indicado
	 * @param set Control set del que obtener su Alt key
	 * @return Comando configurado para la Alt key para en el control set dado
	 */
	std::string getAltKey(const unsigned char set) const;

	/**
	 * Registra para un control set, el comando de su Alt key
	 * @param set Control set en el que registrar la Alt key
	 * @param command Comando a registrar en la Alt key
	 */
	void registerAltKey(const unsigned char set, const std::string& command);

	/**
	 * Obtiene la representación textual del último comando generado
	 * @return Último comando generado en versión textual
	 */
	std::string getLastCommand(void) const;

	/**
	 * Obtiene la configuración actual para un control set indicado
	 * @param set Control set del que se quiere obtener su configuración
	 * @return Configuración del control set para todos los eventos
	 */
	std::vector<std::string> getControlSet(const unsigned char set) const;

	/**
	 * Registra los comandos por defecto de BMonkey para los diferentes control sets
	 */
	void registerDefaultControls(void);

private:

	/**
	 * Obtiene una representación textual de un evento sfml
	 * @param event Evento sfml a transformar
	 * @return Representación textual del evento sfml dado
	 */
	std::string sfmlEventToStr(const sf::Event& event);

	sf::Window* m_window;					/**< Ventana gestionada por el control manager */
	Glib::ustring m_file;					/**< Fichero de configuración usado */
	std::string m_last_command;				/**< Último comando pulsado */
	sf::Vector2i m_mouse_pos;				/**< Última posición del ratón detectada */

	bool m_ignore_alt_key;					/**< Indica si se debe ignorar las Alst keys */
	std::vector<std::string> m_alt_keys;	/**< Configuracion de las alt keys para cada control set */
	std::vector<bool> m_alt_keys_status;	/**< Estados de las Alt keys para cada set */

	std::vector<std::vector<std::string> > m_control_sets;	/**< Configuración de los control sets */
	std::vector<bool> m_events_status;		/**< Estado de cada uno de los eventos */

	static const std::vector<std::string> m_sfml_key_str;	/**< Mapeado a texto de las teclas de sfml */

	static ControlManager* m_control_manager; /**< Instancia única del manager */
};

// Inclusión de los métodos inline
#include "control_manager.inl"

} // namespace bmonkey

#endif // _CONTROL_MANAGER_HPP_
