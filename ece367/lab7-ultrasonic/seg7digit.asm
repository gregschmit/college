; Assembly file for seg7DigitUpdate() function
; Lab 3, ECE 367, fall 2016
; Created by Zhao Zhang

; The 7-segment coding table
                    .data
g_seg7Coding        .byte   00111111b           ; digit 0
                    .byte   00000110b           ; digit 1
                    .byte   01011011b           ; digit 2
                    .byte   01001111b           ; digit 3
                    .byte   01100110b
                    .byte   01101101b
                    .byte   01111101b
                    .byte   00000111b
                    .byte   01111111b
                    .byte   01101111b

; Output code, equivalent to declare "uint8_t code[4]" as static variable
                    .bss    g_code, 4

; Function prototype: seg7DigitUpdate(uint8_t c1, uint8_t c2, uint8_t s1, uint8_t s2);
; The function encoded the digits and calls seg7Update() to display the digits on
; the 4-digit 7-segment display. The colon should always be on.
                    .text
                    .global seg7DigitUpdate     ; make this symbol visible to outside
                    .global seg7Update          ; use this global symbol

; TI assembler requires that symbols in data/bss sections be re-declared in code section before use
seg7Coding          .field  g_seg7Coding
code                .field  g_code


seg7DigitUpdate     PUSH    {lr}

                    LDR r9, seg7Coding
                    LDR r0, [r9, r0]
                    LDR r1, [r9, r1]
                    LDR r2, [r9, r2]
                    LDR r3, [r9, r3]

                    LDR r9, code
                    STRB r0, [r9, #3]
                    ADD r1, #128
                    STRB r1, [r9, #2]
                    STRB r2, [r9, #1]
                    STRB r3, [r9]

                    LDR r0, code

                    ; Call seg7Update(code)
                    BL      seg7Update

                    POP     {lr}
                    BX      lr

                    .end
