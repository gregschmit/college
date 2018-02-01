import math

def f(x):
        return 28.0/5.0 + 2*math.sin(4*x) - 1.0/x

def IntervalArea(leftb, rightb):
        return f(leftb)*(rightb-leftb)

def fArea(leftb, rightb, intervals):
        area = 0
        delta = (rightb-leftb)/intervals
        for i in range(0, intervals):
                area = area + IntervalArea(leftb + i*delta, leftb + (i+1)*delta)
        return area

n = [5, 10, 50, 60, 100]

leftb = float(raw_input("left bound: "))
rightb = float(raw_input("right bound: "))

for k in n:
        print k
        print fArea(leftb, rightb, k)
