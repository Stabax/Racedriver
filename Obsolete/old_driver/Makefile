CC = g++

RM = rm -rf

CXXFLAGS = -std=c++11 -Wall -Wextra -Wshadow -Wpedantic -Wpointer-arith -Wconversion -s -O2 -Os -Icurl/include -Iboost -I.

LDFLAGS = -Lbin -lcurl

NAME = racedriver

BINDIR = bin

SRCDIR = sources

SRCS =  $(SRCDIR)/main.cpp \
				$(SRCDIR)/algos.cpp \
				$(SRCDIR)/Circuit.cpp  \
				$(SRCDIR)/course.cpp  \
				$(SRCDIR)/fonctions.cpp \
				$(SRCDIR)/launcher.cpp  \
				$(SRCDIR)/menus.cpp  \
				$(SRCDIR)/menusPrincipaux.cpp    \
				$(SRCDIR)/sousMenus.cpp    \
				$(SRCDIR)/Moteur.cpp          \
				$(SRCDIR)/Pneus.cpp          \
				$(SRCDIR)/PriseAir.cpp     \
				$(SRCDIR)/Profil.cpp        \
				$(SRCDIR)/Spoiler.cpp  \
				$(SRCDIR)/Voiture.cpp \
				$(SRCDIR)/sha.cpp


OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): clean $(OBJS)
	$(CC) $(OBJS) -o $(BINDIR)/$(NAME) $(LDFLAGS)

clean:
	$(RM) $(SRCDIR)/$(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
