CC = g++
SUBDIRS = src
SOURCES = 
OBJDIR = obj
BINDIR = bin
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = battleship
MOVED_OBJECTS = $(addprefix $(OBJDIR)/, $(OBJECTS))
CPPFLAGS = -O3 -std=c++14

all: $(OBJECTS)
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	$(foreach subdir, $(SUBDIRS), cd $(subdir); make all; cd ../;)
	$(CC) $(OBJDIR)/* -o $(EXECUTABLE)
	mv $(EXECUTABLE) $(BINDIR)

#.cpp.o:
#	$(CC) $(CPPFLAGS) $ < -o $@

.PHONY : clean
clean:
	rm -rf $(BINDIR)/$(EXECUTABLE) $(MOVED_OBJECTS)
	$(foreach subdir,$(SUBDIRS), cd $(subdir); make clean; cd ../;)

