NAME = build/ParseMe

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -lcrypto

SRC = src/main.c src/crypto.c src/storage.c
OBJ = build/main.o build/crypto.o build/storage.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/*.o

fclean: clean
	rm -rf build

re: fclean all

.PHONY: all clean fclean re