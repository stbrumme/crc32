# simple Makefile
#CXX       = g++

# files
PROGRAM   = Crc32Test
LIBS      = -lrt
HEADERS   = Crc32.h
OBJECTS   = Crc32.o Crc32Test.o

# flags
FLAGS     = -O3 -Wall -Wextra -pedantic -s

default: $(PROGRAM)
all: default

$(PROGRAM): $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(FLAGS) $(LIBS) -o $(PROGRAM)

%.o: %.cpp $(HEADERS) Makefile
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)
