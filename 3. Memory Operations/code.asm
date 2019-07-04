;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.

            .data
list1	.word 0,0,0,0
count	.word 0
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

;0x 2be5 1cf0 6549 a0d1

mainloop	push #0x2be5
			push #0x1cf0
			push #0x6549
			push #0xa0d1
			mov.w #list1,r4
			add.w #6,r4
			clrc
			clr r10

loop1		cmp.w #4,count
			jz setlastbit
			inc count
			pop 0(r4)
			rlc.w 0(r4)
			jc carryvar
			jnc carryyok

carryvar	add.w r10,0(r4)
			decd r4
			mov.w #1,r10
			jmp loop1

carryyok	add.w r10,0(r4)
			decd r4
			mov.w #0,r10
			jmp loop1

setlastbit  mov.w #list1,r4
			add.w #6,r4
			add.w r10,0(r4)
			mov.w #0,count
			mov.w #list1,r4
			jmp yerlestir

yerlestir	cmp #4,count
			jz bitti
			inc count
			mov.w SP,r15
			push 0(r4)
			incd r4
			jmp yerlestir

bitti		jmp $


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
            
