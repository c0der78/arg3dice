AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libarg3dice-0.2.la

libarg3dice_0_2_la_SOURCES = dice.cpp yaht/engine.cpp yaht/player.cpp yaht/scoresheet.cpp

libarg3dice_0_2_la_CXXFLAGS = $(LIBARG3DICE_0_2_LA_CXXFLAGS) $(COVERAGE_CFLAGS)

pkginclude_HEADERS = dice.h

subdirheadersdir = $(pkgincludedir)/yaht

subdirheaders_HEADERS = yaht/constants.h yaht/engine.h yaht/player.h yaht/scoresheet.h

