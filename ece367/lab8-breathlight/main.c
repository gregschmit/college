#include <stdbool.h>
#include "pwmled.h"
#include "launchpad.h"

enum sysstate_t {PAUSE, RUN};
enum sysstate_t SYSTEM_ACTIVATED = PAUSE;
enum bcolor_t {WHITE, RED, GREEN, BLUE};
enum bcolor_t BREATH_COLOR = WHITE;

uint8_t UP = 1;
uint8_t BRLO = 1;
uint8_t BRHI = 60;
int16_t BR;
uint32_t DURATION = 50;
uint8_t JUMP = 4;

void event_breath(uint32_t time) {
	//uprintf("setting LED appropriately...\r\n");
	switch (SYSTEM_ACTIVATED) {
		case PAUSE:
			// pwmledSet(0, 0, 0);
			break;
		case RUN:
			if (UP) {
				BR += JUMP;
				if (BR > BRHI) { BR = BRHI; }
				if (BR == BRHI) { UP = 0; }
			} else {
				BR -= JUMP;
				if (BR < BRLO) { BR = BRLO; }
				if (BR == BRLO) { UP = 1; }
			}
			uprintf("BR = %i\r\n", BR);
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
			switch (SYSTEM_ACTIVATED) {
				case PAUSE:
					SYSTEM_ACTIVATED = RUN;
					break;
				case RUN:
					SYSTEM_ACTIVATED = PAUSE;
					break;
			}
			delay = 250;
			break;
		case 2:
			// COLOR CHANGE
			if (SYSTEM_ACTIVATED == RUN) {
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
				delay = 250;
			}
			break;
	}
	schdCallback(event_button, time + delay);
}

int main(void) {
	lpInit();
	pwmledInit();

	schdCallback(event_button, 1000);
	schdCallback(event_breath, 1005);

	uprintf("Running scheduler...\r\n");

	while (1) {
		schdExecute();
	}

	return 0;
}
