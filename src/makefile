SOURCES = battle.cpp main.cpp
OBJDIR = ../obj
OBJECTS = $(SOURCES:.cpp=.o)
MOVED_OBJECTS = $(addprefix ../$(OBJDIR/,$(OBJECTS))
MOVED_OBJECTS = $(addprefix ../$(OBJDIR)/,$(OBJECTS))
INCLUDEPATH = ../
CC = g++
CPPFLAGS = -std=c++14 -c -I$(INCLUDEPATH) 

.PHONY: clean

all: $(OBJECTS) $(SOURCES)
	mv *.o $(OBJDIR)

.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(MOVED_OBJECTS)
