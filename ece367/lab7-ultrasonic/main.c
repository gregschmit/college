/*
 * main.c
 *
 * ECE 367 Lab 7
 *
 * Created by Gregory N. Schmit
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "launchpad.h"
#include "ranger.h"
#include "driverlib/interrupt.h"
#include "seg7.h"
#include "seg7digit.h"

typedef enum {MM, IN} state_t;
uint32_t PAUSE = 0;
static struct {
	state_t state;			// the running state of the stopwatch
	uint8_t s1;
	uint8_t s2;
	uint8_t c1;
	uint8_t c2;
} display = {MM, 0, 0, 0, 0};

void stopWatchUpdate(uint32_t time)
{
    if (PAUSE == 0) {
        float lag_ms = RangerLag() / 50000.0;
        int distance = ((lag_ms*0.34)/2)*1000;
        if (distance > 3000) { distance = 3000; }
        if (display.state == IN) {
            distance = distance/25.4;
        }

        display.s1 = distance/1000;
        distance%=1000;
        display.s2 = distance/100;
        distance%=100;
        display.c1 = distance/10;
        display.c2 = distance % 10;

        seg7DigitUpdate(display.s1, display.s2, display.c1, display.c2);
    }

	schdCallback(stopWatchUpdate, time + 300);
}

void checkPushButton(uint32_t time)
{
	int code = pbRead();
	uint32_t delay;
    switch (code) {
    case 1:
        uprintf("button 1 pushed...\r\n");
        if (PAUSE) { PAUSE = 0;
		} else {
			PAUSE = 1;
		}
        delay = 250;
        break;
    case 2:
        uprintf("button 2 pushed...\r\n");
        if(display.state == MM){
            display.state = IN;
        }
        else {
            display.state = MM;
        }
        delay = 250;
        break;
    default:
        delay = 20;
    }
    schdCallback(checkPushButton, time + delay);
}

void lab7exec(void)
{
    lpInit();
    RangerInit();
    seg7Init();
    seg7DigitUpdate(0, 0, 0, 0);
    uprintf("Lab 7\n\r");
    schdCallback(stopWatchUpdate, 1000);
    schdCallback(checkPushButton, 1005);
	while (true) {
		schdExecute();
	}
}

int main() {
	lab7exec();
	return 0;
}
