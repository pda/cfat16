CC=gcc
CFLAGS=-Wall -pedantic -pedantic-errors
OBJECTS=time.o
BIN=fat

$(BIN): $(OBJECTS) $(BIN).c
	$(CC) $(CFLAGS) $(OBJECTS) $(BIN).c -o $(BIN)

time.o: time.c
	$(CC) $(CFLAGS) -c time.c

clean:
	rm -f $(OBJECTS) $(BIN)
