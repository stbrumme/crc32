# simple Makefile
CPP       = g++

# files
PROGRAM   = Crc32Test
LIBS      =
LIBS_mt   = -lpthread
HEADERS   = Crc32.h
OBJECTS   = Crc32.o Crc32Test.o

OBJECTS2  = Crc32.o Crc32TestMultithreaded.o

# flags
FLAGS     = -O3 -Wall -pedantic -s

default: $(PROGRAM) Crc32TestMultithreaded
all: default

$(PROGRAM): $(OBJECTS) Makefile
	$(CPP) $(OBJECTS) $(FLAGS) $(LIBS) -o $(PROGRAM)

Crc32TestMultithreaded: $(OBJECTS2) Makefile
	$(CPP) $(OBJECTS2) $(FLAGS) $(LIBS_mt) -o Crc32TestMultithreaded

%.o: %.cpp $(HEADERS) Makefile
	$(CPP) $(FLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(OBJECTS2) $(PROGRAM) Crc32TestMultithreaded

run: $(PROGRAM)
	./$(PROGRAM)
