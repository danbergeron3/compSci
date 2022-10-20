CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o bit_flags.o

bit_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o bit_driver $(OBJECTS)

main.o: main.c status.h
	$(CC) $(CFLAGS) -c main.c -o main.o

bit.o: bit_flags.c bit_flags.h
	$(CC) $(CFLAGS) -c bit.c -o bit.o

clean:
	rm -f bit_driver $(OBJECTS)

