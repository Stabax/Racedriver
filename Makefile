##
## Makefile for RaceDriver
## 
## Made by Maxime Martens
##

SRCDIR = src

BINDIR = bin

LIBDIR = thirdparty

##

CXX = g++

RM = rm -rf

CXXFLAGS	= -ggdb -W -Wall -Wpedantic -Iinclude -I$(LIBDIR) -I$(LIBDIR)/json/include/

LDFLAGS		= -L$(BINDIR) -lcurl -static-libgcc

ifeq ($(OS),Windows_NT)
	LDFLAGS += -lpdcurses
else
	LDFLAGS += -lncurses
endif

NAME = $(BINDIR)/Racedriver

SRCS = 	$(SRCDIR)/Game.cpp							\
				$(SRCDIR)/Menu.cpp							\
				$(SRCDIR)/DataFile.cpp					\
				$(SRCDIR)/algos.cpp							\
				$(SRCDIR)/Circuit.cpp						\
				$(SRCDIR)/course.cpp						\
				$(SRCDIR)/main.cpp							\
				$(SRCDIR)/menus.cpp							\
				$(SRCDIR)/menusPrincipaux.cpp		\
				$(SRCDIR)/Engine.cpp						\
				$(SRCDIR)/Tires.cpp							\
				$(SRCDIR)/AirIntake.cpp					\
				$(SRCDIR)/Profil.cpp						\
				$(SRCDIR)/sousMenus.cpp					\
				$(SRCDIR)/Spoiler.cpp						\
				$(SRCDIR)/Terminal.cpp					\
				$(SRCDIR)/Car.cpp								\
				$(LIBDIR)/sha/sha.cpp

OBJS = $(SRCS:.cpp=.o)

#Rules

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
