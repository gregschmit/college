all: pre compile assemble link

pre:
	gcc -E main.c -o main.i
	gcc -E sum.c -o sum.i

compile: pre
	gcc -S main.i -o main.s
	gcc -S sum.i -o sum.s

assemble: compile
	gcc -c main.s -o main.o
	gcc -c sum.s -o sum.o

link: assemble
	gcc main.o sum.o -o lab1

clean:
	rm -f *.i *.s *.o lab1
