CC=g++
CFLAGS=-g

.PHONY all: hello

.PHONY clean:
	rm -f *.o hello

.PHONY debug: clean all
	./hello

hello: main.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@
