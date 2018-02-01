all: labw13

labw13: labw13.o solver.o
	gcc labw13.o solver.o

labw13.o: labw13.c
	gcc -c labw13.c

solver.o: solver.c
	gcc -c solver.c

clean:
	rm -rf *o labw13
