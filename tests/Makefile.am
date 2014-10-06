AUTOMAKE_OPTIONS = subdir-objects

noinst_PROGRAMS = arg3dice_test

arg3dice_test_SOURCES = arg3.test.cpp dice.test.cpp yaht/engine.test.cpp yaht/player.test.cpp yaht/scoresheet.test.cpp

AM_CPPFLAGS = @AM_CPPFLAGS@ -Ivendor/bandit -Wall -Werror

arg3dice_test_LDADD = ../src/libarg3dice-0.2.la

check: arg3dice_test$(EXEEXT)
	./arg3dice_test
