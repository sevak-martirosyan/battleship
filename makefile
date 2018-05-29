CC = g++
SUBDIRS = src
SOURCES = 
OBJDIR = obj
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = battleship
MOVED_OBJECTS = $(addprefix $(OBJDIR/, $(OBJECTS))
CPPFLAGS = -O3 -std=c++14

all: $(OBJECTS)
	mkdir -p $(OBJDIR)
	$(foreach subdir, $(SUBDIRS), cd $(subdir); make all; cd ../;)
	$(CC) $(OBJDIR)/* -o $(EXECUTABLE)

#.cpp.o:
#	$(CC) $(CPPFLAGS) $ < -o $@

.PHONY : clean
clean:
	rm -rf $(EXECUTABLE) $(MOVED_OBJECTS)
	$(foreach subdir,$(SUBDIRS), cd $(subdir); make clean; cd ../;)

