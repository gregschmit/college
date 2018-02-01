FLAGS = -g
DEBUG_FLAGS = $(FLAGS) -Werror -Wall -Wextra -Wno-unused-parameter

all: pre compile assemble link

debug: pre compile assemble
	gcc $(DEBUG_FLAGS) file1gschmi4.o file2gschmi4.o -o main

pre:
	gcc $(FLAGS) -E file1gschmi4.c -o file1gschmi4.i
	gcc $(FLAGS) -E file2gschmi4.c -o file2gschmi4.i

compile: pre
	gcc $(FLAGS) -S file1gschmi4.i -o file1gschmi4.s
	gcc $(FLAGS) -S file2gschmi4.i -o file2gschmi4.s

assemble: compile
	gcc $(FLAGS) -c file1gschmi4.s -o file1gschmi4.o
	gcc $(FLAGS) -c file2gschmi4.s -o file2gschmi4.o

link: assemble
	gcc $(FLAGS) file1gschmi4.o file2gschmi4.o -o main

clean:
	rm -f *.i *.s *.o main
