NAME = build/ParseMe

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC = src/main.c src/parser.c

OBJ = build/main.o build/parser.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -rf build

re: fclean all

.PHONY: all clean fclean re