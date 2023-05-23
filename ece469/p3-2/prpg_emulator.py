#!/usr/local/bin/python3
"""A PRPG CPU simulator. For bitstrings, use `[::-1]` to print."""


import argparse
import subprocess


def b_toint(a):
    b = 1
    y = 0
    for c in a:
        if c == '1': y += b
        b *= 2
    return y

def b_xor(a, b):
    """xor on bitstring encoded as string of '0's and '1's."""
    y = ''
    for i in range(len(a)):
        if a[i] == b[i]: y += '0'
        else: y += '1'
    return y


def b_add(a, b):
    """add two bitstrings encoded as strings of '0's and '1's."""
    y = ''
    c = 0
    for i in range(len(a)):
        ia = int(a[i])
        ib = int(b[i])
        iy = ia+ib+c
        if iy > 1: c = 1
        else: c = 0
        if iy % 2 == 0: y += '0'
        else: y += '1'
    return y


class LFSR:

    def __init__(self):
        self.taps = '0000000'
        self.value = '00000000'
    
    def run(self):
        nx = [''] * len(self.value)
        nx[len(self.taps)] = self.value[0]
        for i in range(len(self.taps)):
            if self.taps[i] == '1':
                nx[i] = b_xor(self.value[i+1], self.value[0])
            else:
                nx[i] = self.value[i+1]
        self.value = ''.join(nx)


class PRPG:

    def __init__(self, instructions, debug=False):
        self.ram = ['00000000'] * 256
        self.r_addr = '00000000'
        self.lfsr = LFSR()
        self.instructions = instructions
        self.pc = 0
        self.halt = 0
        self.debug = debug

    def run(self):
        # debug
        mapping = {
            '000': 'st',
            '001': 'ld',
            '010': 'init_addr',
            '011': 'add',
            '100': 'config',
            '101': 'init_l',
            '110': 'run',
            '111': 'halt',
            }

        if self.debug:
            print("r_addr = " + self.r_addr[::-1])
            print("lfsr = " + self.lfsr.value[::-1])
            print("taps = " + self.lfsr.taps[::-1])

        # fetch instruction
        instr = self.instructions[self.pc]

        # decode (reverse for indexing)
        op = instr[:3]
        immi = instr[3:][::-1]
        taps = instr[4:][::-1]

        # run debug
        if self.debug:
            print("running instruction: " + mapping[op] + ' ' + immi[::-1])

        # do instruction
        if (op == '000'): # st
            self.ram[b_toint(self.r_addr)] = self.lfsr.value
            self.pc += 1
        if (op == '001'): # ld
            self.lfsr.value = self.ram[b_toint(self.r_addr)]
            self.pc += 1
        if (op == '010'): # init_a
            self.r_addr = immi
            self.pc += 1
        if (op == '011'): # add
            self.r_addr = b_add(self.r_addr, immi)
            self.pc += 1
        if (op == '100'): # config
            self.lfsr.taps = taps
            self.pc += 1
        if (op == '101'): # init_l
            self.lfsr.value = immi
            self.pc += 1
        if (op == '110'): # run
            self.lfsr.run()
            self.pc += 1
        if (op == '111'): # halt
            if not self.halt: print("CPU halted")
            self.halt = 1
            pass


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Simulate PRPG CPU.')
    parser.add_argument('-f', '--file', required=True, help='file containing source')
    parser.add_argument('-d', '--debug', action='store_true', help='print debug stuff')
    parser.set_defaults(debug=False)
    args = parser.parse_args()

    instructions = subprocess.run(['./prpg_compiler.py', '-f', args.file], stdout=subprocess.PIPE)

    cpu = PRPG(instructions.stdout.decode().strip().split(), args.debug)

    while (1):
        cpu.run()
        if cpu.halt: break

    # print stuff
    print('final lfsr value: ' + cpu.lfsr.value[::-1])
    print('final r_addr value: ' + cpu.r_addr[::-1])

