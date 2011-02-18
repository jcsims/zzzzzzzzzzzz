.PHONY: clean all

CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=map.c
SRCPATH=src
BUILDDIR=bin
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=zzzzzzzzzzzz

all: $(SRCPATH)/$(SOURCES) $(BUILDDIR)/$(EXECUTABLE)

$(BUILDDIR)/$(EXECUTABLE): $(BUILDDIR)/$(OBJECTS)
	$(CC) $(LDFLAGS) $(BUILDDIR)/$(OBJECTS) -o $@
	
$(BUILDDIR)/%.o: $(SRCPATH)/%.c
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE)