AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libarg3dice.la

libarg3dice_la_LDFLAGS = -version-info 0:0:0

libarg3dice_la_SOURCES = dice.cpp yaht/player.cpp yaht/scoresheet.cpp

libarg3dice_la_CXXFLAGS = $(LIBARG3DICE_LA_CXXFLAGS) $(COVERAGE_CFLAGS)

pkginclude_HEADERS = dice.h

subdirheadersdir = $(pkgincludedir)/yaht

subdirheaders_HEADERS = yaht/constants.h yaht/player.h yaht/scoresheet.h

