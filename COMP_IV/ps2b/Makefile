CC = g++
CFLAGS = -std=c++11 -g -Og -Wall -Werror -pedantic
OBJ = Sokoban.o main.o
LIBS = -lsfml-window -lsfml-graphics -lsfml-system
DEPS = Sokoban.hpp

all: Sokoban lint

Sokoban: $(OBJ)
	$(CC) $(CFLAGS) -o Sokoban $(OBJ) $(LIBS) 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJ) Sokoban