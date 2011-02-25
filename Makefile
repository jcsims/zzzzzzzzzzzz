.PHONY: clean run

CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-lpanel -lcurses
SOURCES=map.c game.c high_score.c engine.c
vpath %.h src
vpath %.c src
vpath %.o Zbin
BUILDDIR=Zbin
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=zzzzzzzzzzzz

$(EXECUTABLE): $(OBJECTS)
#	cd bin; $(CC) $(LDFLAGS) $(OBJECTS) -o $@
	cd $(BUILDDIR); $(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
map.o: map.c map.h
	if [ ! -d $(BUILDDIR) ]; then mkdir $(BUILDDIR); fi
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

game.o: game.c game.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

high_score.o: high_score.c high_score.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

engine.o: engine.c engine.h
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@

clean:
#	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE)
	rm -rf $(BUILDDIR)
run:
#	cd bin; ./$(EXECUTABLE)
	cd $(BUILDDIR); ./$(EXECUTABLE)
