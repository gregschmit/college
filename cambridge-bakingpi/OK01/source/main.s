.section .init
.globl _start
_start:
ldr r0,=0x3f200000
mov r1,#1
lsl r1,#21
str r1,[r0,#16]
mov r1,#1
lsl r1,#15
str r1,[r0,#32]
loop$:
b loop$

