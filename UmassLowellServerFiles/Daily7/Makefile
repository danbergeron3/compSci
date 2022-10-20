CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o stack.o 
stack_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o stack_driver $(OBJECTS)
main.o: main.c status.h
	$(CC) $(CFLAGS) -c main.c -o main.o
stack.o: stack.c stack.h 
	$(CC) $(CFLAGS) -c stack.c -o stack.o
clean:
	rm stack_driver $(OBJECTS)
