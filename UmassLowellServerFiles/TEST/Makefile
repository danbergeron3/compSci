CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o test.o
test_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o test_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
test.o: test.c test.h status.h
	$(CC) $(CFLAGS) -c test.c -o test.o
clean:
	rm test_driver $(OBJECTS)

