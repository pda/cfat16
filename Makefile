CC=gcc
CFLAGS=-Wall -pedantic -pedantic-errors
OBJECTS=filesystem.o boot.o time.o dir.o utils.o
BIN=read_fat

$(BIN): $(OBJECTS) $(BIN).c
	$(CC) $(CFLAGS) $(OBJECTS) $(BIN).c -o $(BIN)

filesystem.o: filesystem.c
	$(CC) $(CFLAGS) -c filesystem.c

boot.o: boot.c
	$(CC) $(CFLAGS) -c boot.c

time.o: time.c
	$(CC) $(CFLAGS) -c time.c

dir.o: dir.c
	$(CC) $(CFLAGS) -c dir.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJECTS) $(BIN)
