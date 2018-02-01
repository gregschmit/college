; Buzzer driver functions built on top of Tivaware
; Lab 4, ECE 367, spring 2017
; Created by Greg Schmit in spring 2017
; Last revised on Feb. 20, 2017

; To include names declared in C header file
 .cdecls "stdint.h", "stdbool.h", "stdio.h", "inc/hw_memmap.h", "driverlib/pin_map.h", "driverlib/gpio.h", "driverlib/sysctl.h", "launchpad.h", "motion.h"

					.text
;					.global motionCheck

; GPIO peripheral, port base and pin mask value for the buzzer
; The buzzer is assumed to be connected to J17, and then the buzzer's
; signal pin is connected to PC4.
MOTION_PERIPH		.field	SYSCTL_PERIPH_GPIOC
MOTION_PORT			.field 	GPIO_PORTC_BASE
MOTION_PIN			.equ	  GPIO_PIN_5


;
; void buzzInit(): Initialze the buzz peripheral, port, and pin direction
;

motionInit			PUSH 	{LR}

					; Initialize the GPIO peripheral for the port that the buzzer uses:
					;   In C: SysCtlPeripheralEnable(BUZZER_PERIPH);
					LDR		r0,	MOTION_PERIPH
					BL		SysCtlPeripheralEnable

					; Set the GPIO pin for the buzzer as output type:
					;   Call GPIOPinTypeGPIOOutput(BUZZER_PORT, BUZZER_PIN)
					LDR		r0,	MOTION_PORT
					MOV		r1, #MOTION_PIN
					BL		GPIOPinTypeGPIOInput

					POP		{PC}

;
; void buzzOn(): Turn on the buzzer. It calls GPIOPinWrite() to write 1 to the signal pin.
;
motionCheck
  push {lr}
  ldr r0, MOTION_PORT
  mov r1, #MOTION_PIN
  bl GPIOPinRead
  pop {pc}
