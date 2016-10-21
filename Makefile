PROGRAM=Crc32Test
LIBS=-lrt
HEADERS=Crc32.h
OBJECTS=Crc32.o Crc32Test.o
FLAGS=-O3 -Wall -pedantic -s
LINKFLAGS=-s
CPP=g++

default: $(PROGRAM)
all: default

Crc32Test: $(OBJECTS)
	$(CPP) $(OBJECTS) $(LIBS) -o $(PROGRAM)

%.o: %.cpp $(HEADERS)
	$(CPP) $(LINKFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)
