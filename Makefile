# simple Makefile
#CXX       = g++

# files
PROGRAM   = Crc32Test
LDLIBS    = -lrt
HEADERS   = Crc32.h
OBJECTS   = Crc32.o Crc32Test.o

# flags
CXXFLAGS  = -O3 -Wall -Wextra -pedantic -s

default: $(PROGRAM)
all: default

$(PROGRAM): $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LDLIBS) -o $(PROGRAM)

%.o: %.cpp $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)
