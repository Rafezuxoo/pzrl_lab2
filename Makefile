CFLAGS = -c -Og -g -Wall -Wextra -Wpedantic -fanalyzer -std=gnu99
NAME = sed_simplified
SRC = ./src/
CC = gcc
FILE = input.txt 's/old_text_regex/new_text/'

.PHONY: run clean all

all: main.o lib2.o
	$(CC) main.o lib2.o -lm -o ${NAME}

main.o: $(SRC)main.c
	$(CC) $(CFLAGS) $(SRC)main.c

lib2.o: $(SRC)lib2.c
	$(CC) $(CFLAGS) $(SRC)lib2.c

run: all clean
	./$(NAME) $(FILE)

clean:
	rm -f *.o
