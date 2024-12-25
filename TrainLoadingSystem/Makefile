CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/train.c src/wagon.c src/material.c src/file_ops.c src/utils.c
OBJ = $(SRC:.c=.o)
TARGET = train_loading_system

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)