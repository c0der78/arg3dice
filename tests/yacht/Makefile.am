

noinst_PROGRAMS = arg3yacht_test

arg3yacht_test_SOURCES = arg3.test.cpp engine.test.cpp player.test.cpp scoresheet.test.cpp ../dice.test.cpp

AM_CPPFLAGS = -std=c++11 -stdlib=libc++ -I../vendor -Wall -Werror -I../../src/yacht

arg3yacht_test_LDADD = ../../src/libarg3dice-0.2.la ../../src/yacht/libarg3yacht-0.2.la
