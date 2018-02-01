/*
 * main.c
 *
 * ECE 367 Lab 1
 *
 * Created by Gregory N. Schmit
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "launchpad.h"

unsigned char g_color = 0;  // 0=white, 1=red, 2=green, 3=blue
short int g_freq = 1000;

void event_LED(uint32_t time)
{
    static enum {OFF, ON} state = OFF;
    int delay = g_freq;
    switch (state) {
    case OFF:
        switch (g_color) {
        case 0:
            ledTurnOnOff(true, true, true);
            break;
        case 1:
            ledTurnOnOff(true, false, false);
            break;
        case 2:
            ledTurnOnOff(false, false, true);
            break;
        default:
            ledTurnOnOff(false, true, false);
            break;
        }
        state = ON;
        break;
    case ON:
        ledTurnOnOff(false, false, false);
        state = OFF;
        break;
    }
    schdCallback(event_LED, time + delay);
}

void event_button(uint32_t time)
{
    int code = pbRead();
    uint32_t delay;
    switch (code) {
    case 1:
        switch (g_freq) {
        case 1000:
            g_freq = 500;
            break;
        case 500:
            g_freq = 2000;
            break;
        default:
            g_freq = 1000;
            break;
        }
        delay = 250;
        break;
    case 2:
        g_color++;
        if (g_color > 3) { g_color = 0; }
        delay = 250;
        break;
    default:
        delay = 10;
    }
    schdCallback(event_button, time + delay);
}

void lab1exec(void)
{
    lpInit();
    uprintf("%s\n\r", "Welcome to ECE367!");
    schdCallback(event_LED, 1000);
    schdCallback(event_button, 1005);
    while (true) {
        schdExecute();
    }
    return;
}

int main() {
	lab1exec();
	return 0;
}
