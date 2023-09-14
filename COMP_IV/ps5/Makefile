CC = g++
CFLAGS = -std=c++11 -g -Og -Wall -Werror -pedantic
OBJ = EDistance.o main.o
LIBS = -lsfml-system 
DEPS = Header/EDistance.hpp

all: EDistance lint

EDistance: $(OBJ)
	$(CC) $(CFLAGS) -o EDistance $(OBJ) $(LIBS) 
lint: 
	cpplint *.cpp *.hpp 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJ) EDistance lint