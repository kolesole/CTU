OBJ1=main.o help_sigterm.o
OBJ2=nsd_main.o nsd.o nd.o
CC=gcc
CFLAGS= -Wall $(EXTRA_CFLAGS)
TARGETS = forkpipe nsd

all: $(TARGETS)

forkpipe: $(OBJ1)
	$(CC) -o $@ $(OBJ1)

nsd: $(OBJ2)
	$(CC) -o $@ $(OBJ2)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

help_sigterm.o: help_sigterm.h

nsd.o: nsd.h

nd.o: nd.h

clean:
	rm -f $(OBJ1) $(OBJ2) forkpipe nsd
