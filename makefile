all: work09.o
	gcc work09.o
work09.o: work09.c
	gcc -c work09.c
run: all
	./a.out .
