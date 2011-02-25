.PHONY: clean run

CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-lcurses -lpanel
SOURCES=map.c game.c high_score.c engine.c
vpath %.h src
vpath %.c src
vpath %.o bin
BUILDDIR=bin
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=zzzzzzzzzzzz

$(EXECUTABLE): $(OBJECTS)
	cd bin; $(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
map.o: map.c map.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

game.o: game.c game.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

high_score.o: high_score.c high_score.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

engine.o: engine.c engine.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE)

run:
	cd bin; ./$(EXECUTABLE)
