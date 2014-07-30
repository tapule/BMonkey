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

#ifndef _I18N_HPP_
#define _I18N_HPP

/*
	Definiciones de macros para internacionalización
*/
#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <libintl.h>


#ifdef _
#undef _
#endif

#ifdef N_
#undef N_
#endif

#ifdef ENABLE_NLS
	#define _(str) gettext(str)
	#ifdef gettext_noop
		#define N_(str) gettext_noop(str)
	#else
		#define N_(str) (str)
	#endif
#else
	#define _(str) (str)
	#define N_(str) (str)
#endif

#endif // _I18N_HPP_
