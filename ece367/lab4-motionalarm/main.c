/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include "launchpad.h"
#include "buzzer.h"
#include "motion.h"

// The state of the buzzer
uint8_t systemState = 0;
uint8_t motionState = 0;
uint32_t alarmCount = 0;
uint32_t backoffTimer = 0;
uint8_t msCounter = 0;

void alarmDaemon(uint32_t time) {
    msCounter++;
    if (msCounter > 9) { msCounter = 0; }
    if (msCounter % 2) { motionState = motionCheck(); }
    if (backoffTimer > 100) {
        backoffTimer-=100;
    } else {
        backoffTimer = 0;
    }
    if (alarmCount >= 100) {
        alarmCount-=100;
        if (!alarmCount) { backoffTimer = 3000; }
    } else {
        alarmCount = 0;
    }
    uprintf("alarm count: %i\r\nbackoff timer: %i\r\nmotion state: %i\r\n", alarmCount, backoffTimer, motionState);
    schdCallback(alarmDaemon, time + 100);
}

void buttonDaemon(uint32_t time) {
	int code = pbRead();
	uint32_t delay;
	switch (code) {
	case 1:
		systemState = 1;
        uprintf("System Engaged\r\n");
		delay = 250;
		break;
	case 2:
		systemState = 0;
        uprintf("System Disabled\r\n");
		delay = 250;
		break;
	default:
		delay = 10;
	}
    schdCallback(buttonDaemon, time + delay);
}

void systemDaemon() {
    while (1) {
        if (systemState) {
            if (alarmCount && !backoffTimer) {
                buzzOn();
                waitUs(700);
                buzzOff();
                waitUs(700);
            } else {
                if (motionState && !backoffTimer) {
                    alarmCount = 3000;
                }
            }
        }
        schdExecute();
    }
}

int main(void)
{
	lpInit();
	buzzInit();
    motionInit();

	uprintf("%s\n\r", "Lab 4 starts");

    schdCallback(buttonDaemon, 1010);
    schdCallback(alarmDaemon, 1010);
    systemDaemon();
}
