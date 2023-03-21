CC = g++
CFLAGS = -std=c++11 -g -Og -Wall -Werror -pedantic
OBJ = PTree.o PTree_driver.o
LIBS = -lsfml-window -lsfml-graphics -lsfml-system 
DEPS = PTree.hpp

all: PTree lint

PTree: $(OBJ)
	$(CC) $(CFLAGS) -o PTree $(OBJ) $(LIBS) 
lint: 
	cpplint *.cpp *.hpp 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJ) PTree lint