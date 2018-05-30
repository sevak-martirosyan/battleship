SOURCES = battle.cpp main.cpp
OBJDIR = ../obj
OBJECTS = $(SOURCES:.cpp=.o)
MOVED_OBJECTS = $(addprefix ./$(OBJDIR)/,$(OBJECTS))
CC = g++
CPPFLAGS = -std=c++14 -c -g

all: $(OBJECTS) $(SOURCES)
	mv *.o $(OBJDIR)

.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(MOVED_OBJECTS)
