# simple Makefile
CPP       = g++

# files
PROGRAM   = Crc32Test
LIBS      =
LIBS_mt   = -lpthread
HEADERS   = Crc32.h
OBJECTS   = Crc32.o Crc32Test.o

OBJECTS2  = Crc32.o Crc32TestMultithreaded.o

OBJECTS3  = Crc32.o Crc32cl.o

# flags
FLAGS     = -O3 -Wall -pedantic -s

default: $(PROGRAM) Crc32TestMultithreaded crc32
all: default

$(PROGRAM): $(OBJECTS) Makefile
	$(CPP) $(OBJECTS) $(FLAGS) $(LIBS) -o $(PROGRAM)

Crc32TestMultithreaded: $(OBJECTS2) Makefile
	$(CPP) $(OBJECTS2) $(FLAGS) $(LIBS_mt) -o Crc32TestMultithreaded

crc32: $(OBJECTS3) Makefile
	$(CPP) $(OBJECTS3) $(FLAGS) $(LIBS) -o crc32

%.o: %.cpp $(HEADERS) Makefile
	$(CPP) $(FLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(OBJECTS2) $(OBJECTS3) $(PROGRAM) Crc32TestMultithreaded crc32

run: $(PROGRAM)
	./$(PROGRAM)
