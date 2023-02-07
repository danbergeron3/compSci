CC = g++
CFLAGS = -std=c++11 -g -Og -Wall -Werror -pedantic
DEPS = FibLFSR.hpp
OBJ = FibLFSR.o PhotoMagic.o 
LIBS = -lsfml-window -lsfml-graphics -lsfml-system

all: ps1B

ps1B: $(OBJ)
	$(CC) $(CFLAGS) -o ps1B $(OBJ) $(LIBS) 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJ) ps1B