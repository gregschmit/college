;****************************************************************
; homework3.asm: Assembly code for homework 3 assignment.
;
; Created by Zhao Zhang, Jan 28, 2017, for ECE 367 spring 2017
;****************************************************************

			.cdecls "homework3.h"		; include the C declarations in homework1.h

			.text

;****************************************************************
; int add2(int a, int b)
;   Return a+b
;****************************************************************
			.global add2
add2
	push {lr}
	add r0, r0, r1
	pop {pc}


;****************************************************************
; int add2(int a, int b, int c)
;   Return add2(add2(a, b), c)
;   Your solution must call add2() function.
;****************************************************************
			.global add3
add3
	push {lr}
	push {r2}
	bl add2
	pop {r1}
	bl add2
	pop {pc}

;****************************************************************
; unsigned fibonacci(usigned n)
;****************************************************************
			.global fibonacci
fibonacci
	push {lr}
	cmp	r0, #1
	ble basecase
	sub r0, r0, #1
	push {r0}
	bl fibonacci
	pop {r1}
	push {r0}
	sub r0, r1, #1
	bl fibonacci
	pop {r1}
	add r0, r0, r1
basecase
	pop {pc}

