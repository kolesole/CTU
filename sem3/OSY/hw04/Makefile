OBJ = main.o linked_list.o producer.o consumer.o
CC = gcc
EXTRA_CFLAGS ?= -fsanitize=address -fno-omit-frame-pointer
CFLAGS = -Wall -g -O2 $(EXTRA_CFLAGS)
TARGET = prod-cons

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	rm -f $(OBJ) $(TARGET)