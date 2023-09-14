CC = g++
CFLAGS = -std=c++11 -g -Og -Wall -Werror -pedantic
OBJ = RandWriter.o test.o
OBJ2 = TextWriter.o RandWriter.o
LIBS = -lsfml-system 
DEPS = Header/RandWriter.hpp

all: TextWriter Test lint

TextWriter: $(OBJ2)
	$(CC) $(CFLAGS) -o RandWriter $(OBJ2) $(LIBS)
Test: $(OBJ)
	$(CC) $(CFLAGS) -o Test $(OBJ) $(LIBS)
lint: 
	cpplint *.cpp Header/RandWriter.hpp
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJ) $(OBJ2) RandWriter Test lint