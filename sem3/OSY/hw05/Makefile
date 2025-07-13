OBJ = main.o utils.o work.o worker.o workers_list.o
CC = gcc
EXTRA_CFLAGS ?= -fsanitize=address -fno-omit-frame-pointer
CFLAGS = -Wall -g -O2 $(EXTRA_CFLAGS)
TARGET = factory

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	rm -f $(OBJ) $(TARGET)
