AUTOMAKE_OPTIONS = subdir-objects

noinst_PROGRAMS = arg3dice_test

arg3dice_test_SOURCES = arg3.test.cpp dice.test.cpp yacht/engine.test.cpp yacht/player.test.cpp yacht/scoresheet.test.cpp

AM_CPPFLAGS = @AM_CPPFLAGS@ -Ivendor/bandit -Wall -Werror

pkginclude_HEADERS = dice.test.h

arg3dice_test_LDADD = ../src/libarg3dice-0.2.la

check: arg3dice_test$(EXEEXT)
	./arg3dice_test
