CC = g++

RM = rm -f

CXXFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Wconversion -Os -s -O2

LDFLAGS = -lsfml-system -lsfml-window -lsfml-graphics

NAME = racedriver

SRCDIR = src

BINDIR = bin

SRCS =	main.cpp

OBJS = $(SRCDIR)/$(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(BINDIR)/$(NAME) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re