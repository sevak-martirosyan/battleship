SOURCES = battle.cpp main.cpp
OBJDIR = ../obj
OBJECTS = $(SOURCES:.cpp=.o)
MOVED_OBJECTS = $(addprefix ../$(OBJDIR/,$(OBJECTS))
MOVED_OBJECTS = $(addprefix ../$(OBJDIR)/,$(OBJECTS))
INCLUDEPATH = ../
CC = g++
CPPFLAGS = -std=c++14 -c -I$(INCLUDEPATH) 

all: $(OBJECTS) $(SOURCES)
	mv *.o $(OBJDIR)

.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(MOVED_OBJECTS)
