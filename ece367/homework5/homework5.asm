;****************************************************************
; homework4.asm: Assembly code template for homework 4 assignment.
;
; Created by Zhao Zhang, Feb. 15, 2017, for ECE 367 spring 2017
;****************************************************************

			.cdecls "homework5.h"		; include the C declarations in homework4.h

			.text

;****************************************************************
; void convert2(uint32_t *pWord)
;   Convert the endian type of *pWord, no use of REV instruction
;****************************************************************
			.global convert2
convert2
	ldrb r1, [r0, #3]
	ldrb r2, [r0, #0]
	strb r1, [r0, #0]
	strb r2, [r0, #3]
	ldrb r1, [r0, #2]
	ldrb r2, [r0, #1]
	strb r1, [r0, #1]
	strb r2, [r0, #2]
			BX		lr

;****************************************************************
; void convert2(uint32_t *pWord)
;   Convert the endian type of *pWord, using REV instruction
;****************************************************************
			.global convert3
convert3
	ldr r1, [r0motionalarm]
	rev r1, r1
	str r1, [r0]
			BX		lr
