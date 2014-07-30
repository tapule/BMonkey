## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_DOC_DIR=\""$(prefix)/doc"\" \
	$(GLIBMM_CFLAGS) \
	$(LIBXML_CFLAGS) \
	$(FFMPEG_CFLAGS) \
	$(SFML_CFLAGS) \
	$(OGL_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = \
	bmonkeyfe

bmonkeyfe_SOURCES = \
	defines.hpp \
	bmonkey/bmonkey_main.cpp \
	bmonkey/bmonkey.hpp \
	bmonkey/bmonkey.cpp \
 	utils/config.cpp \
	utils/config.hpp \
	utils/crc32.cpp \
	utils/crc32.hpp \
	utils/debug.hpp \
	utils/i18n.hpp \
	utils/log.hpp \
	utils/os_detect.hpp \
	utils/parser.cpp \
	utils/parser.hpp \
	utils/process.cpp \
	utils/process.hpp \
	utils/tokenizer.cpp \
	utils/tokenizer.hpp \
	utils/utils.cpp \
	utils/utils.hpp \
	utils/xml_parser.cpp \
	utils/xml_parser.hpp \
	utils/xml_reader.cpp \
	utils/xml_reader.hpp \
	utils/xml_writer.cpp \
	utils/xml_writer.hpp

bmonkeyfe_LDFLAGS = 

bmonkeyfe_LDADD = \
	$(GLIBMM_LIBS) \
	$(LIBXML_LIBS) \
	$(FFMPEG_LIBS) \
	$(SFML_LIBS) \
	$(OGL_LIBS)

# Limpieza de ficheros con "make maintainerclean"
MAINTAINERCLEANFILES = \
	config.h \
	config.h.in \
	Makefile \
	Makefile.in

