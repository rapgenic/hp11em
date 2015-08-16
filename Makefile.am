bin_PROGRAMS = hp11em

hp11em_SOURCES = src/AMS.cpp \
	src/calcdrawarea.cpp \
	src/core.cpp \
	src/core_math.cpp \
	src/debugwindow.cpp \
	src/dispdrawarea.cpp \
	src/keys.cpp \
	src/main.cpp \
	src/mainwindow.cpp \
	src/signals.cpp \
	src/SR.cpp

LDADD = $(GTKMM_LIBS) $(CLN_LIBS)
	
AM_CPPFLAGS = $(GTKMM_CFLAGS) $(CLN_CFLAGS) -I$(top_srcdir)/images -Wno-write-strings
