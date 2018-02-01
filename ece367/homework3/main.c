/*
 * main.c for homework 3
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "launchpad.h"
#include "homework3.h"

int main(void)
{
    lpInit();

    uprintf("\n\rTest add2()\n\r");

    // Test add2()
    uprintf("add2(%d, %d) = %d\n\r", 1, 2, add2(1, 2));
    uprintf("add2(%d, %d) = %d\n\r", 10, -5, add2(10, -5));
    uprintf("add2(%d, %d) = %d\n\r", -3, 0, add2(-3, 0));

    // Test add3()
    uprintf("\n\rTest add3()\n\r");
    uprintf("add3(%d, %d, %d) = %d\n\r", 1, 2, 3, add3(1, 2, 3));
    uprintf("add3(%d, %d, %d) = %d\n\r", -1, 2, 3, add3(-1, 2, 3));
    uprintf("add3(%d, %d, %d) = %d\n\r", 0, 10, -5, add3(0, 10, -5));
    uprintf("add3(%d, %d, %d) = %d\n\r", -5, -10, -15, add3(-5, -10, -15));

    // Test fibonacci()
    uprintf("\n\rTest fibonacci()\n\r");
    uprintf("fibonacci(%u) = %u\n\r", 0, fibonacci(0));
    uprintf("fibonacci(%u) = %u\n\r", 1, fibonacci(1));
    uprintf("fibonacci(%u) = %u\n\r", 2, fibonacci(2));
    uprintf("fibonacci(%u) = %u\n\r", 3, fibonacci(3));
    uprintf("fibonacci(%u) = %u\n\r", 4, fibonacci(4));
    uprintf("fibonacci(%u) = %u\n\r", 5, fibonacci(5));
    uprintf("fibonacci(%u) = %u\n\r", 6, fibonacci(6));
    uprintf("fibonacci(%u) = %u\n\r", 7, fibonacci(7));

    // Print a message to make sure the program doesn't crash
    uprintf("\n\rTest done, no crash seems to have happened.\n\r");

    // Never exit
    while (true) {
    }
}
