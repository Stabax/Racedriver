CC = g++

RM = rm -f

INCDIR = include

SRCDIR = src

BINDIR = bin

LDFLAGS = -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics

ifeq ($(OS),Windows_NT)
	CXXFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR)
	NAME = racedriver-win32
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
	CXXFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR) -I/usr/include
	NAME = racedriver-linux
  endif
  ifeq ($(UNAME_S),Darwin)
	CXXFLAGS = -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR) -I/usr/local/include
	LDFLAGS += -L/usr/local/lib
	NAME = racedriver-macos
  endif
endif

SRCS =	$(SRCDIR)/main.cpp							\
				$(SRCDIR)/Pipeline.cpp				\
				$(SRCDIR)/GameEngine.cpp			\
				$(SRCDIR)/HUD.cpp				\
				$(SRCDIR)/Player.cpp				\
				$(SRCDIR)/Menus/Menu.cpp			\
				$(SRCDIR)/Menus/MainMenu.cpp			\
				$(SRCDIR)/Part.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(BINDIR)/$(NAME) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
