CC = g++
CFLAGS = -std=c++11 -g -Og -Wall -Werror -pedantic
OBJ = main.o Checkers.o
LIBS = -lsfml-window -lsfml-graphics -lsfml-system 
DEPS = Checkers.hpp

all: Checkers lint

Checkers: $(OBJ)
	$(CC) $(CFLAGS) -o Checkers $(OBJ) $(LIBS) 
lint: 
	cpplint *.cpp Headers/Checkers.hpp 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJ) Checkers lint