CC= g++
LD = g++

INCDIRS="-I./include/"
LIBDIRS="-Linclude/"
BINDIR="bin/"

CXXFLAGS= --std=c++11 -Wall
LDFLAGS=
SOURCES= src/main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CXXFLAGS) $(INCDIRS) $< -o $@
