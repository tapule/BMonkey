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

#ifndef _XML_PARSER_HPP_
#define _XML_PARSER_HPP_

#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>
#include <libxml2/libxml/parser.h>
#include <map>


/**
 * Implementación de un parser XML basado en SAX para la lectura de ficheros xml
 * de forma óptima.
 *
 * Proporciona una serie de señales que indicarán el estado del parseo del
 * ficheros xml pasando los datos correspondientes de cada estado.
 */
class XmlParser
{
public:
	/**
	 * Constructor básico
	 */
	XmlParser();

	/**
	 * Destructor de la clase
	 */
	virtual ~XmlParser(void){}

	/**
	 * Ejecuta el parseo del fichero indicado
	 * @param file Fichero xml que parsear
	 * @return true si se pudo ejecutar el parser, false en otro caso
	 * @note Para el correcto funcionamiento del parser, las señales deben ser
	 * conectadas antes de llamar a este método.
	 */
	bool parse(const Glib::ustring& file);

	/**
	 * Interfaz para acceder a la señal que indica el inicio del documento xml
	 * @return Señal correspondiente.
	 * @note Mediante este método un huesped se podrá conectar a la señal del
	 * parser que indica el comienzo de un documento xml
	 */
	sigc::signal<void> signalStartDocument(void){
		return m_signal_start_document;
	}

	/**
	 * Interfaz para acceder a la señal que indica el fin del documento xml
	 * @return Señal correspondiente.
	 * @note Mediante este método un huesped se podrá conectar a la señal del
	 * parser que indica la finalización de un documento xml
	 */
	sigc::signal<void> signalEndDocument(void){
		return m_signal_end_document;
	}

	/**
	 * Interfaz para acceder a la señal que indica el inicio de un elemento xml
	 * @return Señal correspondiente.
	 * @note Mediante este método un huesped se podrá conectar a la señal del
	 * parser que indica el comienzo de un elemento xml. La señal pasará como
	 * parámetros, el nombre del elemento y un mapa con sus atributos.
	 */
	sigc::signal<void, Glib::ustring&, std::map<Glib::ustring, Glib::ustring >& > signalStartElement(void){
		return m_signal_start_element;
	}

	/**
	 * Interfaz para acceder a la señal que indica el fin de un elemento xml
	 * @return Señal correspondiente.
	 * @note Mediante este método un huesped se podrá conectar a la señal del
	 * parser que indica la finalización de un elemento xml. La señal pasará
	 * como parámetro, el nombre del elemento que finaliza.
	 */
	sigc::signal<void, Glib::ustring& > signalEndElement(void){
		return m_signal_end_element;
	}

	/**
	 * Interfaz para acceder a la señal que indica el contenido de un elemento
	 * xml.
	 * @return Señal correspondiente.
	 * @note Mediante este método un huesped se podrá conectar a la señal del
	 * parser que indica que se está accediendo al contenido de un elemento xml.
	 * La señal pasará como parámetro, el contenido del elemento.
	 */
	sigc::signal<void, Glib::ustring& > signalContent(void){
		return m_signal_content;
	}

	/**
	 * Interfaz para acceder a la señal que avisa de pequeños problemas en la
	 * estructura del xml.
	 * @return Señal correspondiente.
	 * @note Mediante este método un huesped podrá ser avisado de problemas en
	 * la estructura del fichero xml. El nivel de estos problemas es warning y
	 * la señal pasará como parámetro una cadena indicando el problema.
	 */
	sigc::signal<void, Glib::ustring& > signalWarning(void){
		return m_signal_warning;
	}

	/**
	 * Interfaz para acceder a la señal que avisa de errores no críticos en el
	 * parseo del xml.
	 * @return Señal correspondiente.
	 * @note Mediante este método un huesped podrá ser avisado de errores no
	 * críticos en la estructura del fichero xml. El nivel de estos problemas es
	 * error y la señal pasará como parámetro una cadena indicando el problema.
	 */
	sigc::signal<void, Glib::ustring& > signalError(void){
		return m_signal_error;
	}

	/**
	 * Interfaz para acceder a la señal que avisa de errores críticos en el
	 * parseo del xml.
	 * @return Señal correspondiente.
	 * @note Mediante este método un huesped podrá ser avisado de errores
	 * críticos en la estructura del fichero xml. El nivel de estos problemas es
	 * fatal error y la señal pasará como parámetro una cadena indicando el
	 * problema.
	 */
	sigc::signal<void, Glib::ustring& > signalFatalError(void){
		return m_signal_fatal_error;
	}

private:
	/**
	 * Callback para el parser sax que gestionara el inicio del documento.
	 * @param data Datos de usuario
	 */
	static void onStartDocument(void* data);

	/**
	 * Callback para el parser sax que gestionara el fin del documento.
	 * @param data Datos de usuario
	 */
	static void onEndDocument(void* data);

	/**
	 * Callback para el parser sax que gestionará el inicio de un elemento xml
	 * @param data Datos de usuario
	 * @param name Nombre del elemento procesado
	 * @param attributes Listado de atributos y sus valores
	 */
	static void onStartElement(void* data, const xmlChar* name, const xmlChar** attributes);

	/**
	 * Callback para el parser sax que gestionará el fin de un elemento xml
	 * @param data Datos de usuario
	 * @param name Nombre del elemento procesado
	 */
	static void onEndElement(void* data, const xmlChar* name);

	/**
	 * Callback para el parser sax que gestionará el contenido de un elemento
	 * xml
	 * @param data Datos de usuario
	 * @param content Contenido del elemento xml
	 * @param length Longitud del contenido en p_content
	 */
	static void onContent(void* data, const xmlChar* content, int length);

	/**
	 * Callback que se encarga de gestionar las entidades xml (&...)
	 * @param data Datos de usuario
	 * @param name Entidad xml
	 * @return Traducción de la entidad xml
	 */
	static xmlEntityPtr	onGetEntity(void* data, const xmlChar* name){
		return xmlGetPredefinedEntity(name);
	}

	/**
	 * Callback para gestionar pequeños problemas en la estructura del xml
	 * @param data Datos de usuario
	 * @param msg Mensaje para transmitir
	 * @param ... Parámetros extra para el mensaje
	 */
	static void onWarning(void* data, const char* msg, ...);

	/**
	 * Callback para gestionar errores no críticos en la estructura del xml
	 * @param data Datos de usuario
	 * @param msg Mensaje para transmitir
	 * @param ... Parámetros extra para el mensaje
	 */
	static void onError(void* data, const char* msg, ...);

	/**
	 * Callback para gestionar errores críticos en la estructura del xml
	 * @param data Datos de usuario
	 * @param msg Mensaje para transmitir
	 * @param ... Parámetros extra para el mensaje
	 */
	static void onFatalError(void* data, const char* msg, ...);

	// Señales emitidas por la clase
	sigc::signal<void> m_signal_start_document;					/**< Indica el comienzo de un documento xml */
	sigc::signal<void> m_signal_end_document;					/**< Indica el final de un documento xml */
	sigc::signal<void, Glib::ustring&, std::map<Glib::ustring, Glib::ustring >& > m_signal_start_element;	/**< Indica el comienzo de un elemento xml */
	sigc::signal<void, Glib::ustring& > m_signal_end_element;	/**< Indica el final de un elemento xml */
	sigc::signal<void, Glib::ustring& > m_signal_content;		/**< Indica el contenido de un elemento xml */
	sigc::signal<void, Glib::ustring& > m_signal_warning;		/**< Indica un problema en el parseo */
	sigc::signal<void, Glib::ustring& > m_signal_error;			/**< Indica un error en el parseo */
	sigc::signal<void, Glib::ustring& > m_signal_fatal_error;	/**< Indica un error fatal en el parseo */

	xmlSAXHandler m_sax_handler;	/**< Handler de callbacks para el parser sax */
};

#endif // _XML_PARSER_HPP_
