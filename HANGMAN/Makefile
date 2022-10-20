CC = gcc
CFLAGS = -g -Wall --std=c99 -Wfatal-errors -Wno-unused-variable
OBJECTS = main.o my_string.o generic_vector.o hangman.o avl_tree.o
OBJECT2 = my_string.o unit_test.o test_def.o generic_vector.o	
ALL = main.o my_string.o generic_vector.o unit_test.o test_def.o hangman.o avl_tree.o
string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
hangman.o: hangman.c hangman.h
	$(CC) $(CFLAGS) -c hangman.c -o hangman.o
generic_vector.o: generic_vector.c generic.h generic_vector.h
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o	
unit_test.o: unit_test.c unit_test.h	
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
my_string.o: my_string.c my_string.h status.h
	$(CC) $(CFLAGS) -c my_string.c  -o my_string.o
avl_tree.o: avl_tree.c avl_tree.h
	$(CC) $(CFLAGS) -c avl_tree.c -o avl_tree.o
unit_test: $(OBJECT2)
	$(CC) $(CFLAGS) -o unit_test $(OBJECT2) 
clean: 
	rm -f $(ALL) 



	
