/*
 * main.c for homework 5
 * ECE 367, Spring 2017
 * Created by Zhao Zhang, Feb. 15 2017
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "launchpad.h"

#include "homework5.h"

int main(void)
{
	uint32_t n;

	lpInit();

	// Test convert2(), and convert3()
	uprintf("\n\rTest convert2() and convert3()\n\r");

	n = 0x87654321;
	convert2(&n);
	uprintf("convert2(0x%x) = 0x%x\n\r", 0x87654321, n);

	n = 0x87654321;
	convert3(&n);
	uprintf("convert3(0x%x) = 0x%x\n\r", 0x87654321, n);

	// Print a message to make sure the program doesn't crash
	uprintf("\n\rTest done, no crash seems to have happened.\n\r");

	// Never exit
	while (true) {
	}
}
