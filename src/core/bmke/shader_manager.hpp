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

#ifndef _SHADER_MANAGER_HPP_
#define _SHADER_MANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "../../defines.hpp"

namespace bmonkey{

/**
 * Gestiona los shaders del sistema
 *
 * Se encarga de mantener y gestionar los shaders soportados por el frontend.
 * Mantiene un almacen con los shaders, estos se pueden cargar y descargar bajo
 * demanda.
 * La lista de posibles shaders es fija, no permite cargar desde fichero.
 * Únicamente permite una instancia de la clase al mismo tiempo.
 */
class ShaderManager
{
public:

	// Tipos de los posibles shaders gestionados por el ShaderManager
	enum Type
	{
		TEST = 0,		/**< Shader de prueba */
		COUNT			/**< Contador de shaders */
	};

	/**
	 * Constructor de la clase
	 */
	ShaderManager(void);

	/**
	 * Destructor de la clase
	 */
	virtual ~ShaderManager(void);

	/**
	 * Indica si la tarjeta gráfica soporta shaders
	 * @return true si la tarjeta soporta shaders, false en otro caso
	 */
	bool isAvailable(void);

	/**
	 * Carga un shader determinado
	 * @param shader Identificador del shader a cargar
	 * @return true Si se pudo realizar la carga, false en otro caso.
	 */
	bool loadShader(const Type type);

	/**
	 * Obtiene un shader determinado por su identificador
	 * @param effect Effecto a reproducir
	 * @note Si el shader no está cargado, lo carga previamente
	 */
	sf::Shader* getShader(const Type type);

	/**
	 * Elimina el shader indicado por su identificador
	 * @param shader Identificador del shader a eliminar
	 */
	void deleteShader(const Type type);

	/**
	 * Limpia el ShaderManager liberando todos los shaders cargados
	 */
	void clean(void);

private:
	static bool m_instantiated;				/**< Indica si ya hay una instancia de la clase */

	std::vector<sf::Shader* > m_shaders;	/**< Vector almacen de shaders */
	static const std::vector<std::vector<std::string> > m_shaders_src; /**< Código fuente de los shaders soportados */
};

} // namespace bmonkey

#endif // _SHADER_MANAGER_HPP_
