from sys import argv

script, input_file = argv

def print_all(f):
        print f.read()

def rewind(f):
        f.seek(0)

def print_a_line(line_count, f):
        print line_count, f.readline()

current_file = open(input_file)

print "First let's print the whole file:"

print_all(current_file)

print "Now let's rewind."

rewind(current_file)

print "Let's print three lines:"

for i in [1,2,3]:
        current_line = i
        print_a_line(current_line, current_file)
