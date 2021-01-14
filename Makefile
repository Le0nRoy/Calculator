CC=g++
CFLAGS=-g

.PHONY all: hello.o

.PHONY clean:
	rm -f *.o 

.PHONY debug: clean all
	./hello.o

hello.o: main.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@
