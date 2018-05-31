CC = g++
SUBDIRS = src
OBJDIR = obj
BINDIR = bin
DOXY   = ./docs/doxy
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = battleship
MOVED_OBJECTS = $(addprefix $(OBJDIR)/, $(OBJECTS))
CPPFLAGS = -O3 -std=c++14

all: $(OBJECTS)
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(DOXY)
	$(foreach subdir, $(SUBDIRS), cd $(subdir); make all; cd ../;)
	$(CC) $(OBJDIR)/* -o $(EXECUTABLE)
	mv $(EXECUTABLE) $(BINDIR)


.PHONY : clean doxygen
doxygen:
	@doxygen	./docs/Doxyfile
clean:
	rm -rf $(BINDIR) $(OBJDIR) $(DOXY) 
	$(foreach subdir,$(SUBDIRS), cd $(subdir); make clean; cd ../;)
    

