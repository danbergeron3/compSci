CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o queue.o
q_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o q_driver $(OBJECTS)
main.o: main.c status.h
	$(CC) $(CFLAGS) -c main.c -o main.o
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c -o queue.o
clean:
	rm q_driver $(OBJECTS)

