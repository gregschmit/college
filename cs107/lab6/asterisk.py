import sys
import random

def PrintAsterisks():
        r = int((random.random()*10)//1)
        print r
        for i in range(0, r):
                sys.stdout.write('*')
        sys.stdout.write('\n')

for i in range(0, 10):
        PrintAsterisks()
