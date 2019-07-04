;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

	;Question1
	;1 – Load the number 123 to R9. Move this value to R7.
	mov.w #123,r9
	mov.w r9,r7

	;Question2
	;2 – Load the number 0x4400 to R5. Load the number 99 to R6. Store the contents of R6 to the memory at the address in R5.
	mov.w #0x4400,r5
	mov.w #99,r6
	mov.w r6,0(r5)

	;Question3
	;3 – Continuing from 2, load the contents of the memory at the address 0x4400 to R5.
	mov.w &0x4400,r5

	;Question4
	;4 – Starting from the address 0x4400, store the numbers 11, 22, 33, 44 to the memory as bytes. Mind the endian ordering.
	;Kisisel Not: Endian ordering'in ne onemi var burada, word yazmiyoruz ki?
	mov.b #11,&0x4400
	mov.b #22,&0x4401
	mov.b #33,&0x4402
	mov.b #44,&0x4403

	;Question5
	;5 – Continuing from 4, add the numbers stored to the memory and store the result in R6.
	add.b &0x4400,&0x4401
	add.b &0x4401,&0x4402
	add.b &0x4402,&0x4403
	mov.b &0x4403,r6


;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
