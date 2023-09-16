CC = gcc
CFLAGS = -Wall -Wextra
TARGET = meu_servidor
SRCS = main.c amqp.c
HEADERS = amqp.h

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean

all: $(TARGET)
