CC = g++

RM = rm -f

INCDIR = include

SRCDIR = src

BINDIR = bin

CXXFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Wconversion -Os -s -O2 -I$(INCDIR)

LDFLAGS = -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics

NAME = racedriver

SRCS =	$(SRCDIR)/main.cpp		\
	$(SRCDIR)/GameEngine.cpp	\
	$(SRCDIR)/Menu.cpp		\
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