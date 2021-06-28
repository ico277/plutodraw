CC=gcc
SOURCES=plutodraw.c
CFLAGS=-lpluto -O3
EXECUTABLE=plutodraw
PREFIX=/usr/local/bin

TESTSOURCES=test.c
TESTCFLAGS=-lpluto -O3
TESTEXECUTABLE=test

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install: all
	cp $(EXECUTABLE) $(PREFIX)/

uninstall:
	rm -f $(PREFIX)/$(EXECUTABLE)

run: all
	./$(EXECUTABLE)

clean: $(EXECUTABLE)
	rm -f $(EXECUTABLE)

test:
	$(CC) $(TESTSOURCES) $(TESTCFLAGS) -o $(TESTEXECUTABLE)
	./$(TESTEXECUTABLE)
	rm ./$(TESTEXECUTABLE)