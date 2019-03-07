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
CXXFLAGS += -I$(LIBDIR) -I$(LIBDIR)/lua/
CXXFLAGS += -I$(LIBDIR)/omniunit/include/omniunit/ -I$(LIBDIR)/sol2/ -I$(LIBDIR)/cpp-httplib/ -I$(LIBDIR)/MenuFramework/include/
CXXFLAGS += -I$(LIBDIR)/MenuFramework/$(LIBDIR)/json/include/ -I$(LIBDIR)/MenuFramework/$(LIBDIR)/pugixml/src/ 
CXXFLAGS += -I$(LIBDIR)/MenuFramework/$(LIBDIR)/lua/ -I$(LIBDIR)/MenuFramework/$(LIBDIR)/sol2/

# -static-libgcc

ifeq ($(OS),Windows_NT)
	MAKE = mingw32-make
	LDFLAGS = -L$(LIBDIR)/pdcurses/wincon/ -lpdcurses -lws2_32 $(LIBDIR)/MenuFramework/lib/MenuFramework.a $(LIBDIR)/MenuFramework/thirdparty/lua/liblua.a
else
	MAKE = make
	LDFLAGS = -lncurses
endif

NAME = $(BINDIR)/Racedriver

SRCS = 	$(SRCDIR)/Terminal.cpp							\
				$(SRCDIR)/Input.cpp									\
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
				$(SRCDIR)/Accident.cpp

OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
RES = $(RESDIR)/racedriver.res
endif

#Rules

all: game

deps:
ifeq ($(OS),Windows_NT)
	-cd $(LIBDIR)/pdcurses/wincon/ && $(MAKE) DLL=Y
	-cd $(LIBDIR)/MenuFramework/ && $(MAKE)
	-windres $(RESDIR)/racedriver.rc -O coff -o $(RESDIR)/racedriver.res
else
	-cd $(LIBDIR)/MenuFramework/ && $(MAKE)
endif

game:	$(info ****************** Run "make deps" before compiling game *****************) $(OBJS)
	$(CXX) $(OBJS) $(RES) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

cleandeps:
ifeq ($(OS),Windows_NT)
	-cd $(LIBDIR)/MenuFramework/ && $(MAKE) clean
	-$(RM) $(RESDIR)/racedriver.res
else
	-cd $(LIBDIR)/MenuFramework/ && $(MAKE) clean
endif

re: fclean all

.PHONY: all clean fclean re
