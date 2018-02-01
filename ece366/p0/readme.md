# Project 0 - Tool Familiarization

ECE366 Computer Organization, Fall 2017

## Description/Meta

This homework assignment consists of building a circuit in LogicWorks 5 and writing some MIPS code.

Author: Gregory N. Schmit (gschmi4@uic.edu)

Date: 14 September 2017

## Part 1 - LogicWorks

I built a 10->5 MUX to determine whether we push init values to the register or use the sum and B to repopulate the registers.

I then built the fibonacci circuit.

I then put the fibonacci circuit into my "main" circuit and put in the IO devices in.

## Part 2 - MIPS

### Remainder Program

This one was fairly easy. I implemented an algorithm that repeatedly subtracted along with some error finding code. On error, the code returns -1 as a flag.

### Third Largest

This one was harder. My algorithm traverses the list three times to find largest each time (ignoring already found indices).
