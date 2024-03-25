CC = gcc
CFLAGS = -Wall -ansi -pedantic

list: symtablelist.o testsymtab.o
	$(CC) -o testsymtab testsymtab.o symtablelist.o

hash: symtable.h symtablehash.o
	$(CC) $(CFLAGS) -o testsymtab testsymtab.c symtablehash.o

symtablehash.o: symtable.h symtablehash.c
	$(CC) $(CFLAGS) -c symtablehash.c

symtablelist.o: symtable.h symtablelist.c
	$(CC) $(CFLAGS) -c symtablelist.c

testsymtab.o: symtable.h testsymtab.c
	$(CC) $(CFLAGS) -c testsymtab.c

clean:
	rm -rf *.o
	rm -rf testsymtab.exe
