CC = g++
CFLAGS = -std=c++11 -c -g -Og -Wall -Werror -pedantic
DEPS = FibLFSR.hpp
OBJ = FibLFSR.o main.o
OBJ_A = FibLFSR.o test.o
LIBS = -lboost_unit_test_framework

all: ps1 driver

ps1: $(OBJ) $(DEPS)
	$(CC) $(CFLAGs) -o ps1 $(OBJ)
driver: $(OBJ_A) $(DEPS) 
	$(CC) $(CFLAGs) -o driver $(OBJ_A) $(LIBS)
test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp -o test.o
main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp -o main.o
FibLFSR.o: FibLFSR.cpp FibLFSR.hpp
	$(CC) $(FLAGS) -c FibLFSR.cpp -o FibLFSR.o
clean:
	rm -f $(OBJ) main.o test.o ps1 driver