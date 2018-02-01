/*
 * main.c
 *
 *  Created on: Jan 30, 2017
 *      Author: Gregory N. Schmit
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <driverlib/sysctl.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_i2c.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/i2c.h>
#include "launchpad.h"
#include "seg7.h"

// 7-segment coding table. See https://en.wikipedia.org/wiki/Seven-segment_display. The segments
// are named as A, B, C, D, E, F, G. In this coding table, segments A-G are mapped to bits 0-7.
// Bit 7 is not used in the coding. This display uses active high signal, in which '1' turns ON a
// segment, and '0' turns OFF a segment.
static uint8_t seg7Coding[10] = {
        0b00111111,         // digit 0
        0b00000110,         // digit 1
        0b01011011,         // digit 2
        0b01001111,         // digit 3
        0b01100110,         // 4
        0b01101101,         // 5
        0b01111101,         // 6
        0b00000111,         // 7
        0b01111111,         // 8
        0b01101111          // 9
};

static uint8_t g_colon = 0b10000000;
static uint8_t g_colon_mask = 0b10000000;
static uint8_t g_fulltick = 1;
static int8_t g_second = 0;
static int8_t g_second_tens = 0;
static int8_t g_minute = 0;
static int8_t g_minute_tens = 0;

void clock_sanity()
{
    if (g_second > 9) {
        g_second_tens+=(g_second / 10);
        g_second = g_second % 10;
    } else if (g_second < 0) {
        g_second_tens-=((-g_second + 9) / 10);
        g_second = (g_second % 10) + 10;
    }
    if (g_second_tens > 5) {
        g_minute+=(g_second_tens / 6);
        g_second_tens = g_second_tens % 6;
    } else if (g_second_tens < 0) {
        g_minute-=((-g_second_tens + 5) / 6);
        g_second_tens = (g_second_tens % 6) + 6;
    }
    if (g_minute > 9) {
        g_minute_tens+=(g_minute / 10);
        g_minute = g_minute % 10;
    } else if (g_minute < 0) {
        g_minute_tens-=((-g_minute + 9) / 10);
        g_minute = (g_minute % 10) + 10;
    }
    if (g_minute_tens > 9 || g_minute_tens < 0) {
        g_minute_tens = 0;
        g_minute = 0;
        g_second_tens = 0;
        g_second = 0;
    }
}

void set_clock()
{
    uint8_t code[4];
    code[0] = seg7Coding[g_second];
    code[1] = seg7Coding[g_second_tens];
    code[2] = seg7Coding[g_minute] + g_colon;
    code[3] = seg7Coding[g_minute_tens];
    seg7Update(code);
}

void event_clockhalftick(uint32_t time)
{
    g_colon = g_colon^g_colon_mask;
    g_fulltick = !g_fulltick;
    if (g_fulltick) {
        g_second++;
        clock_sanity();
    }
    set_clock();
    schdCallback(event_clockhalftick, time + 500);
}

void event_button(uint32_t time)
{
    int code = pbRead();
    uint32_t delay;
    switch (code) {
    case 1:
        g_minute++;;
        clock_sanity();
        set_clock();
        delay = 250;
        break;
    case 2:
        g_second++;;
        clock_sanity();
        set_clock();
        delay = 250;
        break;
    default:
        delay = 10;
        break;
    }
    schdCallback(event_button, time + delay);
}

int main(void)
{
    lpInit();
    seg7Init();

    uprintf("%s\n\r", "Lab 2: Wall Clock");

    schdCallback(event_clockhalftick, 1000);
    schdCallback(event_button, 1005);

    while (true) {
        schdExecute();
    }
}
