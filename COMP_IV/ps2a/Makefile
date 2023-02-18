CC = g++
CFLAGS = -std=c++11 -g -Og -Wall -Werror -pedantic
OBJ = Sokoban.o main.o
LIBS = -lsfml-window -lsfml-graphics -lsfml-system
DEPS = Sokoban.hpp

all: test

test: $(OBJ)
	$(CC) $(CFLAGS) -o test $(OBJ) $(LIBS) 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJ) test