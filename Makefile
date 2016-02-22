all: main.c sorted-list.o
	gcc -o main main.c sorted-list.o

sorted-list.o: sorted-list.c sorted-list.h
	gcc -c sorted-list.c

clean:
	rm *.o 
	rm ./generic-sorter
