import random

EPSILON = .1     # tolerated error for the guessing game

def within(value, target):
    if target < value + EPSILON and target > value - EPSILON:
        return 1
    else:
        return 0

r = random.randrange(0, 10000)
r/=100.00

print "I am thinking of a number between 0 and 100. Guess the number."
guess = float(raw_input("Guess: "))
while (not within(guess, r)):
    if guess < r:
        print "too low"
    else:
        print "too high"
    guess = float(raw_input("Guess: "))

print "Good job! You're within %.2f of the true value of %.2f" % (EPSILON, r)
