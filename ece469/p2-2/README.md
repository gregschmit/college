# Project 2, Part 2 -- PRPG CPU

## About

The CPU is SystemVerilog. The compiler and emulator are both Python 3 and expects your Python 3 interpreter to be located at `/usr/local/bin/python3`.

See `decoder.sv` for the instruction opcodes.

## Compiler (Python 3)

To compile a program (e.g., `prog1.asm`):

    $ ./prpg_compile.py -f prog1.asm

## CPU Emulator (Python 3)

To run a program:

    $ ./prpg_emulator.py -f prog1.asm

To show debugging info (values between each instruction):

    $ ./prpg_emulator.py -f prog1.asm -d
