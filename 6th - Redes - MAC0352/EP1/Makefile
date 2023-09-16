CC = gcc
CFLAGS = -Wall -Wextra
TARGET = main
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/amqp.c
HEADERS = $(SRC_DIR)/amqp.h

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean

all: $(TARGET)

