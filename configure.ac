# Process this file with autoconf to produce a configure script.

# Inicializamos autoconf
AC_INIT(bmonkey, 0.0.1, bmonkeyfe@gmail.com)

# Inicializamos automake e indicamos que se cree config.h con autoheader
#AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_INIT_AUTOMAKE()
AM_CONFIG_HEADER(src/config.h)
AM_MAINTAINER_MODE

AC_CONFIG_MACRO_DIR([m4])

# Comprobaciones varias
AC_ISC_POSIX
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11
AM_PROG_CC_STDC
AC_HEADER_STDC

# Determinamos el tipo de host para colocar la ayuda
# Esto es solo un test para configuraciones condicionales
#AC_CANONICAL_HOST

#case "$host_os" in

#linux*)
	# Documentación de gnome en help
	#GNOME_DOC_INIT
#	;;

#*)
#	;;
#esac


# Generamos un define en config.h con la web del programa
PACKAGE_WEBSITE=http://bmonekey.sourceforge.net
AC_SUBST(PACKAGE_WEBSITE)
AC_DEFINE_UNQUOTED(PACKAGE_WEBSITE,"$PACKAGE_WEBSITE", [BMonkey website])

# Internacionalización
GETTEXT_PACKAGE=bmoneky
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])
AM_PROG_LIBTOOL

# Comprobamos las librerías gtkmm3 y exportamos sus flags
#PKG_CHECK_MODULES(GTKMM, [gtkmm-3.0 glibmm-2.4 giomm-2.4])
#AC_SUBST(GTKMM_CFLAGS)
#AC_SUBST(GTKMM_LIBS)

# Comprobamos las librerías glibmm y exportamos sus flags
PKG_CHECK_MODULES(GLIBMM, [glibmm-2.4 giomm-2.4])
AC_SUBST(GLIBMM_CFLAGS)
AC_SUBST(GLIBMM_LIBS)

# Comprobamos la librería libxml y exportamos sus flags
PKG_CHECK_MODULES(LIBXML, [libxml-2.0])
AC_SUBST(LIBXML_CFLAGS)
AC_SUBST(LIBXML_LIBS)

# Comprobamos la librería libcurl y exportamos sus flags
#PKG_CHECK_MODULES(CURL, [libcurl])
#AC_SUBST(CURL_CFLAGS)
#AC_SUBST(CURL_LIBS)

# Comprobamos las librerías ffmpeg y exportamos sus flags
PKG_CHECK_MODULES(FFMPEG, [libavutil >= 50 libavformat >= 52 libavcodec >= 52 libswscale >= 0.7.0 libswresample])
CXXFLAGS="$CXXFLAGS -D__STDC_CONSTANT_MACROS"
AC_SUBST(FFMPEG_CFLAGS)
AC_SUBST(FFMPEG_LIBS)

# Comprobamos las librerías sfml y exportamos sus flags
PKG_CHECK_MODULES(SFML, [sfml-all >= 2.0])
#PKG_CHECK_MODULES(SFML, [sfml-graphics >= 2])
#PKG_CHECK_MODULES(SFML, [sfml-system >= 2])
#PKG_CHECK_MODULES(SFML, [sfml-audio >= 2])
AC_SUBST(SFML_CFLAGS)
AC_SUBST(SFML_LIBS)

# Comprobamos las librerías OpenGL y exportamos sus flags
OGL_CFLAGS="-pthread"
OGL_LIBS="-lpthread"

AC_CHECK_LIB(GL, glEnable,
    [ OGL_LIBS="$OGL_LIBS -lGL -lm" ],
    [ AC_MSG_ERROR("GL not found") ])

AC_CHECK_LIB(GLU, gluProject,
    [ OGL_LIBS="$OGL_LIBS -lGLU" ],
    [ AC_MSG_ERROR("GLU not found") ])

AC_CHECK_LIB(glut, glutInit,
    [ OGL_LIBS="$OGL_LIBS -lglut  -lSM -lICE -lXmu -lXi" ],
    [ AC_MSG_ERROR("glut not found") ])
AC_SUBST(OGL_CFLAGS)
AC_SUBST(OGL_LIBS)

# Comprobamos parámetros
#    Activar modo debug --enable-debug
AC_ARG_ENABLE(debug, [AC_HELP_STRING([--enable-debug],[build with debug support [default=no]])],,[enable_debug=no])
if test "x$enable_debug" = "xyes"; then
	AC_DEFINE(ENABLE_DEBUG_MODE,1, [Activate debug mode])
fi

#    Activar modo local --enable-localmode
AC_ARG_ENABLE(localmode, [AC_HELP_STRING([--enable-localmode],[build with local mode enabled [default=no]])],,[enable_localmode=no])
if test "x$enable_localmode" = "xyes"; then
	AC_DEFINE(ENABLE_LOCAL_MODE,1, [Activate local mode])
fi

# Indicamos los ficheros que debe generar autoconf a partir de ficheros in
AC_CONFIG_FILES([
	Makefile
	data/Makefile
	data/fonts/Makefile
	data/themes/Makefile
	data/themes/default/Makefile
	doc/Makefile
	help/Makefile
	po/Makefile.in
	src/Makefile
])

AC_OUTPUT

# Mensaje de configuración

echo ""
echo "======================================================================"
echo ""
echo "$PACKAGE_NAME configuration:"
echo "  C compiler              : $CC"
echo "  C++ compiler            : $CXX"
echo "  Prefix                  : $prefix"
echo ""
echo "$PACKAGE_NAME features:"
echo "  Debug support           : $enable_debug"
echo "  Local mode              : $enable_localmode"
echo ""
echo "The following options will be passed to the compiler:"
echo "  CFLAGS: $CFLAGS"
echo "  CXXFLAGS: $CXXFLAGS"
#echo ""
#echo "  GTKMM_CFLAGS: $GTKMM_CFLAGS"
#echo ""
#echo "  GTKMM_LIBS: $GTKMM_LIBS"
echo ""
echo "  GLIBMM_CFLAGS: $GLIBMM_CFLAGS"
echo ""
echo "  GLIBMM_LIBS: $GLIBMM_LIBS"
echo ""
echo "  LIBXML_CFLAGS: $LIBXML_CFLAGS"
echo ""
echo "  LIBXML_LIBS: $LIBXML_LIBS"
#echo ""
#echo "  CURL_CFLAGS: $CURL_CFLAGS"
#echo ""
#echo "  CURL_LIBS: $CURL_LIBS"
echo ""
echo "  FFMPEG_CFLAGS: $FFMPEG_CFLAGS"
echo ""
echo "  FFMPEG_LIBS: $FFMPEG_LIBS"
echo ""
echo "  SFML_CFLAGS: $SFML_CFLAGS"
echo ""
echo "  SFML_LIBS: $SFML_LIBS"
echo ""
echo "======================================================================"
echo ""

