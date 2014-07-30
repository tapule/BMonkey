## File created by the gnome-build tools

# Indicamos los subdirectorios a procesar
SUBDIRS = \
	fonts \
	themes

# Reglas para los icono del programa
bmonkey_icondir = $(datadir)/icons/hicolor/scalable/apps
bmonkey_icon_DATA = bmonkey.svg
bmonkey_winicondir = $(datadir)/bmonkey
bmonkey_winicon_DATA = bmonkey.png

# Reglas para el fichero .desktop
desktopdir = $(datadir)/applications
desktop_in_files = \
	bmonkey.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

# Incluimos los iconos y el fichero .dektop in en la distribución
EXTRA_DIST = \
	$(bmonkey_icon_DATA) \
	$(bmonkey_winicon_DATA) \
	$(desktop_in_files)

# Indicamos que se deben eliminar los ficheros de datos con clean
CLEANFILES = \
	$(desktop_DATA)

# Limpieza de ficheros con "make maintainerclean"
MAINTAINERCLEANFILES = \
	Makefile \
	Makefile.in
