# Lab 9 (Server UART) - Group 4

## Summary

We extended lab8 (breathlight) with UART so that two Launchpads would act as one.

 - Driver for UART
 - Event driven UART checking and sending

## Questions

 1. Work breakdown:
    - Greg (33%)
    - Esteban (33%)
    - Yara (33%)
 2. We added four driver functions:
    1. `void UARTCustomInit();` - Initialization
    2. `void UARTCustomPutChar(char data);` - Putting a char on the wire
    3. `int32_t UARTCustomGetChar();` - Getting a char from the queue
    4. `int UARTCustomCharsAvail();` - Check if any characters are in the queue
 3. The two launchpads communicate via character codes to send commands to each other that do the same thing as SW1 and SW2. We only used one codebase installed on both nodes so they form a partnership rather than a server/client relationship.
 4. Memory usage:
    - Flash: 15,674 bytes
    - SRAM:  1,319 bytes
 5. Our group took about 5 hours to complete this lab.

## Authors

 - Gregory N. Schmit
 - Esteban Garcia
 - Yara Merei
