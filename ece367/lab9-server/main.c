#include <stdbool.h>
#include "pwmled.h"
#include "launchpad.h"
#include "uart.h"

enum sysstate_t {PAUSE, RUN};
enum sysstate_t SYSTEM_ACTIVATED = PAUSE;
enum bcolor_t {WHITE, RED, GREEN, BLUE};
enum bcolor_t BREATH_COLOR = WHITE;

uint8_t UP = 1;
uint8_t BRLO = 1;
uint8_t BRHI = 30;
int16_t BR;
uint32_t DURATION = 5;
uint8_t JUMP = 1;
uint8_t SKIP = 0;
uint8_t SKIP_TOP = 5;

// Dict:
// a - START/PAUSE
// b - COLOR CHANGE

void pause_start() {
    switch (SYSTEM_ACTIVATED) {
        case PAUSE:
            SYSTEM_ACTIVATED = RUN;
            break;
        case RUN:
            SYSTEM_ACTIVATED = PAUSE;
            break;
    }
    return;
}

void change_color() {
    if (SYSTEM_ACTIVATED) {
        switch (BREATH_COLOR) {
            case WHITE:
                BREATH_COLOR = RED;
                break;
            case RED:
                BREATH_COLOR = BLUE;
                break;
            case BLUE:
                BREATH_COLOR = GREEN;
                break;
            case GREEN:
                BREATH_COLOR = WHITE;
                break;
        }
    }
    return;
}

void event_breath(uint32_t time) {
	//uprintf("setting LED appropriately...\r\n");
	// see if update came from other machine
	if (UARTCustomCharsAvail()) {
		int32_t data = UARTCustomGetChar();
		uprintf("data = %i\r\n", data);
		if (data > 96 && data < 123) {
			// data recieved and is valid
			if (data == 'a') {
				uprintf("Pushed sw1 remotely\r\n");
                pause_start();
			} else if (data == 'b') {
				uprintf("Pushed sw2 remotely\r\n");
                change_color();
			}
		}
	}
	switch (SYSTEM_ACTIVATED) {
		case PAUSE:
			// pwmledSet(0, 0, 0);
			break;
		case RUN:
            SKIP++;
            if (SKIP >= SKIP_TOP) {
    			if (UP) {
    				BR += JUMP;
    				if (BR > BRHI) { BR = BRHI; }
    				if (BR == BRHI) { UP = 0; }
    			} else {
    				BR -= JUMP;
    				if (BR < BRLO) { BR = BRLO; }
    				if (BR == BRLO) { UP = 1; }
    			}
    			// uprintf("BR = %i\r\n", BR);
    			switch (BREATH_COLOR) {
    				case WHITE:
    					pwmledSet(BR, BR, BR);
    					break;
    				case RED:
    					pwmledSet(BR, 0, 0);
    					break;
    				case GREEN:
    					pwmledSet(0, BR, 0);
    					break;
    				case BLUE:
    					pwmledSet(0, 0, BR);
    					break;
    			}
                SKIP = 0;
            }
			break;
	}
	schdCallback(event_breath, time + DURATION);
}

void event_button(uint32_t time) {
	uint32_t delay = 20;
	int code = pbRead();
	switch (code) {
		case 1:
            // START/PAUSE
			uprintf("sw1 pushed locally\r\n");
			UARTCustomPutChar('a');
			pause_start();
			delay = 250;
			break;
		case 2:
            // COLOR CHANGE
			uprintf("sw2 pushed locally\r\n");
			UARTCustomPutChar('b');
			change_color();
			delay = 250;
			break;
	}
	schdCallback(event_button, time + delay);
}

int main(void) {
	lpInit();
	pwmledInit();
	UARTCustomInit();

	schdCallback(event_button, 1000);
	schdCallback(event_breath, 1005);

	uprintf("Running scheduler...\r\n");

	while (1) {
		schdExecute();
	}

	return 0;
}
