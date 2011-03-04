.PHONY: clean run all

CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-lpanel -lmenu -lcurses
SOURCES=map.c game.c high_score.c engine.c
vpath %.h src
vpath %.c src
vpath %.o Zbin
BUILDDIR=Zbin
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=zzzzzzzzzzzz

all: $(BUILDDIR)/$(EXECUTABLE)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	cd $(BUILDDIR); $(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	
map.o: map.c map.h defs.h
	if [ ! -d $(BUILDDIR) ]; then mkdir $(BUILDDIR); fi
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

game.o: game.c game.h defs.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

high_score.o: high_score.c high_score.h defs.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

engine.o: engine.c engine.h defs.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

clean:
	rm -rf $(BUILDDIR)
run:
	cd $(BUILDDIR); ./$(EXECUTABLE)
