CC= clang++
LD = clang++

INCDIRS=-I./include/
LIBDIRS=-Linclude/
BINDIR=bin/
SRCDIR=src/

CXXFLAGS= -c --std=c++11 -Wall
LDFLAGS=
SOURCES= $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= $(BINDIR)test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CXXFLAGS) $(INCDIRS) $< -o $@


clean:
	rm $(EXECUTABLE) $(OBJECTS)
