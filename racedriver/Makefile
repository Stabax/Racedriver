CC = g++

RM = rm -f

INCDIR = include

SRCDIR = src

BINDIR = bin

LDFLAGS = -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics

ifeq ($(OS),Windows_NT)
	CXXFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR)
	NAME = $(BINDIR)/racedriver-win32
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
	CXXFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR) -I/usr/include
	NAME = $(BINDIR)/racedriver-linux
  endif
  ifeq ($(UNAME_S),Darwin)
	CXXFLAGS = -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR) -I/usr/local/include
	LDFLAGS += -L/usr/local/lib
	NAME = $(BINDIR)/racedriver-macos
  endif
endif

SRCS =	$(SRCDIR)/main.cpp							\
				$(SRCDIR)/Pipeline.cpp				\
				$(SRCDIR)/GameEngine.cpp			\
				$(SRCDIR)/MusicBox.cpp				\
				$(SRCDIR)/HUD.cpp				\
				$(SRCDIR)/Part.cpp				\
				$(SRCDIR)/Player.cpp				\
				$(SRCDIR)/Menus/Menu.cpp			\
				$(SRCDIR)/Menus/MainMenu.cpp			\
				$(SRCDIR)/Menus/ProfileMenu.cpp			\
				$(SRCDIR)/Menus/OptionsMenu.cpp			\
				$(SRCDIR)/Menus/SettingsMenu.cpp	#	\
				$(SRCDIR)/Filesystem/Basic_File.cpp		\
				$(SRCDIR)/Filesystem/File.cpp		\
				$(SRCDIR)/Filesystem/general_exceptions.cpp		\
				$(SRCDIR)/Filesystem/GroupedKeyWordFile.cpp		\
				$(SRCDIR)/Filesystem/KeyWordFile.cpp		\
				$(SRCDIR)/Filesystem/system_exceptions.cpp		\

OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
