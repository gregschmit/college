all: pre compile assemble link

pre:
	gcc -E main.c -o main.i

compile: pre
	gcc -S main.i -o main.s

assemble: compile
	gcc -c main.s -o main.o

link: assemble
	gcc -static main.o -o lab3static

clean:
	rm -f *.i *.s *.o lab1
