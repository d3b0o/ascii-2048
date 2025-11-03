TARGET = 2048

CC = gcc

CFLAGS = -Wall -Wextra -std=c11

SRC = main.c board.c game.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all

