#!/usr/local/bin/python3

# Compile instructions to machine code (in ASCII, line-separated)


import argparse


class CompileException(Exception):

    def __init__(self, *args, **kwargs):
        super(CompileException, self).__init__("Compiler error!")


def convert_bitstring(bs):
    if len(bs) > 3:
        return format(int(bs, 2), '08b')
    else:
        return format(int(bs), '08b')


def compile_instruction(instr):
    """
    Compiles a single instruction. Returns a string of 11 bits or None.
    """
    if not isinstance(instr, str):
        return None
    instr = [x.lower().strip(';') for x in instr.split()]
    if instr[0].startswith('con'):
        if len(instr) != 2:
            return None
        return '100' + convert_bitstring(instr[1])
    elif instr[0] == 'init_l':
        if len(instr) != 2:
            return None
        return '101' + convert_bitstring(instr[1])
    elif instr[0].startswith('run'):
        return '110' + '00000000'
    elif instr[0] == 'halt':
        return '111' + '00000000'
    elif instr[0].startswith('st'):
        return '000' + '00000000'
    elif instr[0].startswith('ld'):
        return '001' + '00000000'
    elif instr[0].startswith('init_a'):
        if len(instr) != 2:
            return None
        return '010' + convert_bitstring(instr[1])
    elif instr[0].startswith('add'):
        if len(instr) != 2:
            return None
        return '011' + convert_bitstring(instr[1])
    return None


def compile_file(filename):
    result = ''
    with open(filename) as f:
        for n, line in enumerate(f, 1):
            for instr in line.split(';'):
                if instr.strip() != '':
                    mach = compile_instruction(instr)
                    if not mach:
                        raise CompileException("Compile error on line " + str(n))
                    result += mach + '\n'
    return result.strip()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Compile instructions to PRPG processor machine code.')
    parser.add_argument('-f', '--file', help='file containing source')
    args = parser.parse_args()

    if args.file:
        print(compile_file(args.file))

    while (1 and not args.file):
        instr = input("Instruction: ")
        if instr == 'quit' or instr == 'exit':
            break
        mach = compile_instruction(instr)
        if mach:
            print("Machine code: " + mach)
        else:
            print("Error, bad instruction!")
