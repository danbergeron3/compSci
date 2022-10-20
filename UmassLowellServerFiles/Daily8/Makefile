CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o priority_queue.o
pq_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o pq_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(CFLAGS) -c priority_queue.c -o priority_queue.o
clean:
	rm stack_driver $(OBJECTS)
