all: gameoflife; \

gameoflife: gameoflife.o life_engine.o; \
        gcc -o gameoflife gameoflife.o life_engine.o

gameoflife.o: gameoflife.c; \
        gcc -c gameoflife.c

life_engine.o: life_engine.c; \
        gcc -c life_engine.c

clean:; \
        rm *.o gameoflife
