/* drivers for ultrasonic ranger and timer (we will use timer WT0, Timer A) */
#include "ranger.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "launchpad.h"

uint8_t SIGNALHIGH = 0;
uint32_t TIME1 = 0;
uint32_t TIME2 = 0;

void RangerInit() {
    // Enable timer
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER0)) {}
    // Enable GPIO port C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // setup the timer
    TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP);
    TimerControlEvent(WTIMER0_BASE, TIMER_A, TIMER_EVENT_BOTH_EDGES);
    TimerIntClear(WTIMER0_BASE, TIMER_CAPA_EVENT);
    TimerEnable(WTIMER0_BASE, TIMER_A);
    return;
}

void RangerPing() {
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
    waitUs(2);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
    waitUs(5);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
    TimerIntClear(WTIMER0_BASE, TIMER_CAPA_EVENT);
    return;
}

uint32_t RangerLag() {
    RangerPing();
    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PC4_WT0CCP0);
    while(!TimerIntStatus(WTIMER0_BASE, false)) {}
    TIME1 = TimerValueGet(WTIMER0_BASE, TIMER_A);
    TimerIntClear(WTIMER0_BASE, TIMER_CAPA_EVENT);
    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PC4_WT0CCP0);
    while(!TimerIntStatus(WTIMER0_BASE, false)) {}
    TIME2 = TimerValueGet(WTIMER0_BASE, TIMER_A);
    TimerIntClear(WTIMER0_BASE, TIMER_CAPA_EVENT);
    uprintf("After Ping:\r\n  TIME1=%lu\r\n  TIME2=%lu\r\n", TIME1, TIME2);
    return TIME2-TIME1;
}

void RangerRead() {
    if (SIGNALHIGH) {
        TIME2 = TimerValueGet(WTIMER0_BASE, TIMER_A);
    } else {
        TIME1 = TimerValueGet(WTIMER0_BASE, TIMER_A);
    }
    TimerIntClear(WTIMER0_BASE, TIMER_CAPA_EVENT);
    return;
}
