CFLAGS = -c -Og -Wall -Wextra -Wpedantic -fanalyzer -std=c99
NAME = sed_simplified
SRC = ./src/
CC = gcc
FILE = example.txt

.PHONY: run clean all

all: main.o lib2.o
	$(CC) main.o lib2.o -lm -o ${NAME}

main.o: 
	$(CC) $(CFLAGS) $(SRC)main.c

lib2.o:
	$(CC) $(CFLAGS) $(SRC)lib2.c

run: all clean
	./$(NAME) $(FILE)

clean:
	rm -f *.o
