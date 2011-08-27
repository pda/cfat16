CC=gcc
CFLAGS=-Wall -pedantic -pedantic-errors
OBJECTS=time.o dir.o
BIN=fat

$(BIN): $(OBJECTS) $(BIN).c
	$(CC) $(CFLAGS) $(OBJECTS) $(BIN).c -o $(BIN)

time.o: time.c
	$(CC) $(CFLAGS) -c time.c

dir.o: dir.c
	$(CC) $(CFLAGS) -c dir.c

clean:
	rm -f $(OBJECTS) $(BIN)
