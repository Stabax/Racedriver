##
## Makefile for RaceDriver
##
## Made by Maxime Martens
##

SRCDIR = src

BINDIR = bin

RESDIR = resource

LIBDIR = thirdparty


##

CMAKE = cmake

CXX = g++

RM = rm -rf

CXXFLAGS	= -std=c++17 -ggdb -W -Wall -Wpedantic -Iinclude
CXXFLAGS += -I$(LIBDIR) -I$(LIBDIR)/json/include/ -I$(LIBDIR)/pugixml/src/ -I$(LIBDIR)/lua/
CXXFLAGS += -I$(LIBDIR)/omniunit/include/omniunit/ -I$(LIBDIR)/sol2/ -I$(LIBDIR)/cpp-httplib/

LDFLAGS		= -L$(LIBDIR)/lua/ -llua
# -static-libgcc

ifeq ($(OS),Windows_NT)
	MAKE = mingw32-make
	LDFLAGS += -L$(LIBDIR)/pdcurses/wincon/ -lpdcurses -lws2_32
else
	MAKE = make
	LDFLAGS += -lncurses
endif

NAME = $(BINDIR)/Racedriver

SRCS = 	$(SRCDIR)/Menu/Localization.cpp			\
				$(SRCDIR)/Menu/GraphicsRenderer.cpp	\
				$(SRCDIR)/Menu/Menu.cpp							\
				$(SRCDIR)/Menu/MenuItem.cpp					\
				$(SRCDIR)/Menu/ScriptEngine.cpp			\
				$(SRCDIR)/Menu/DataFile.cpp					\
				$(SRCDIR)/Terminal.cpp							\
				$(SRCDIR)/main.cpp									\
				$(SRCDIR)/Game.cpp									\
				$(SRCDIR)/Profile.cpp								\
				$(SRCDIR)/Track.cpp									\
				$(SRCDIR)/Race.cpp									\
				$(SRCDIR)/cppMenus.cpp							\
				$(SRCDIR)/Engine.cpp								\
				$(SRCDIR)/Tires.cpp									\
				$(SRCDIR)/Garage.cpp								\
				$(SRCDIR)/Spoiler.cpp								\
				$(SRCDIR)/Car.cpp										\
				$(SRCDIR)/Accident.cpp							\
				$(LIBDIR)/pugixml/src/pugixml.cpp

OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
RES = $(RESDIR)/racedriver.res
endif

#Rules

all: game

deps:
ifeq ($(OS),Windows_NT)
	-cd $(LIBDIR)/pdcurses/wincon/ && $(MAKE) DLL=Y
	-cd $(LIBDIR)/lua/ && $(MAKE) mingw
	-windres $(RESDIR)/racedriver.rc -O coff -o $(RESDIR)/racedriver.res
else
	-cd $(LIBDIR)/lua/ && $(MAKE) linux
endif

game:	$(info ****************** Run "make deps" before compiling game *****************) $(OBJS)
	$(CXX) $(OBJS) $(RES) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

cleandeps:
ifeq ($(OS),Windows_NT)
	-cd $(LIBDIR)/lua/ && $(MAKE) clean
	-$(RM) $(RESDIR)/racedriver.res
else
	-cd $(LIBDIR)/lua/ && $(MAKE) clean
endif

re: fclean all

.PHONY: all clean fclean re
