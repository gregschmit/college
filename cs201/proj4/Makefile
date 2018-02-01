all: gschmi4-proj4

gschmi4-proj4: gschmi4-proj4.o solveSK.o solver.o
	cc gschmi4-proj4.o solveSK.o solver.o -o gschmi4-proj4

gschmi4-proj4.o: gschmi4-proj4.c
	cc -c gschmi4-proj4.c

solveSK.o: solveSK.c
	cc -c solveSK.c

solver.o: solver.c
	cc -c solver.c

clean:
	rm -rf *o gschmi4-proj4
