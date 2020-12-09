CC=g++
CFLAGS=-g

.PHONY all: hello.o

.PHONY clean:
	rm -f *.o 

.PHONY debug: clean all
	./hello.o

hello.o: main.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@
