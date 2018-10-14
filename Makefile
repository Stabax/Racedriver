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

CXXFLAGS	= -g3 -W -Wall -Wpedantic -Iinclude -I$(LIBDIR)

LDFLAGS		= -L$(BINDIR) -lcurl -static-libgcc

ifeq ($(OS),Windows_NT)
	LDFLAGS += -lpdcurses
else
	LDFLAGS += -lncurses
endif

NAME = $(BINDIR)/Racedriver

SRCS = 	$(SRCDIR)/Game.cpp							\
				$(SRCDIR)/Menu.cpp							\
				$(SRCDIR)/algos.cpp							\
				$(SRCDIR)/Circuit.cpp						\
				$(SRCDIR)/course.cpp						\
				$(SRCDIR)/main.cpp							\
				$(SRCDIR)/menus.cpp							\
				$(SRCDIR)/menusPrincipaux.cpp		\
				$(SRCDIR)/Moteur.cpp						\
				$(SRCDIR)/Pneus.cpp							\
				$(SRCDIR)/PriseAir.cpp					\
				$(SRCDIR)/Profil.cpp						\
				$(SRCDIR)/sousMenus.cpp					\
				$(SRCDIR)/Spoiler.cpp						\
				$(SRCDIR)/Terminal.cpp					\
				$(SRCDIR)/Voiture.cpp						\
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
