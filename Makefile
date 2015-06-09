CC = g++

RM = rm -rf

CFLAGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wfloat-equal -Woverloaded-virtual  -Winline -std=c++0x -Wconversion -Os -s -O2 -lboost_thread -lcurl -lsfml-system -lsfml-window -lsfml-graphics

NAME = conqueror

SRCS =	main.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re