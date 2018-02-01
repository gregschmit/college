#include <stdint.h>
#include <stdbool.h>
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "launchpad.h"


// PF1 - T0CCP1
// PF2 - T1CCP0
// PF3 - T1CCP1

void pwmledInit()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)) {}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinConfigure(GPIO_PF1_T0CCP1);
    GPIOPinConfigure(GPIO_PF2_T1CCP0);
    GPIOPinConfigure(GPIO_PF3_T1CCP1);
}

void pwmledSet(uint8_t R, uint8_t G, uint8_t B)
{
    uint16_t LoadSet = 10000;
    uint16_t RMatchSet = (1.0 - (R / 255.0)) * LoadSet;
    uint16_t GMatchSet = (1.0 - (G / 255.0)) * LoadSet;
    uint16_t BMatchSet = (1.0 - (B / 255.0)) * LoadSet;
    TimerDisable(TIMER0_BASE, TIMER_B);
    TimerDisable(TIMER1_BASE, TIMER_B);
    TimerDisable(TIMER1_BASE, TIMER_A);
    if (R) {
        TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
        TimerLoadSet(TIMER0_BASE, TIMER_B, LoadSet);
        TimerMatchSet(TIMER0_BASE, TIMER_B, RMatchSet);
        TimerEnable(TIMER0_BASE, TIMER_B);
    }
    uint32_t tmpCFG = (TIMER_CFG_B_PWM*!!G) | (TIMER_CFG_A_PWM*!!B);
    uint32_t tmpTIMER = (TIMER_B*!!G) | (TIMER_A*!!B);
    if (G || B) {
        TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | tmpCFG);
        TimerLoadSet(TIMER1_BASE, TIMER_B, LoadSet);
        TimerMatchSet(TIMER1_BASE, TIMER_B, GMatchSet);
        TimerLoadSet(TIMER1_BASE, TIMER_A, LoadSet);
        TimerMatchSet(TIMER1_BASE, TIMER_A, BMatchSet);
        TimerEnable(TIMER1_BASE, tmpTIMER);
    }
    return;
}
