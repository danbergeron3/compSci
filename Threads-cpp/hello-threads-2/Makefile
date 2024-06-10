CC= g++
CFLAGS= -std=c++14 -g -Og -Wall -Werror -pedantic -fext-numeric-literals
OBJ= hello-threads.o 

Threads: $(OBJ)
	$(CC) $(CFLAGS) -o Threads $(OBJ) 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) Threads lint