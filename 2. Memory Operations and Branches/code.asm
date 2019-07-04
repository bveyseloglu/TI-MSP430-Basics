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
array1	.word	9712, 2454, 1275, 3312, 4243, 2395, 4387, 12236, 9454, 32221
arrayRef .word 0
			.bss section1,20
			.bss sectionRef,1
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

;1 – Using assembler directives, create an array in the memory, and initialize it with the numbers below (use .word):
;9712, 2454, 1275, 3312, 4243, 2395, 4387, 12236, 9454, 32221
;2 – Find the number of elements that are greater than 10000 in the array created in step 1 and store the result in R9.

main1		clr r9 ;r9u sifirlayalim
			mov.w #array1, r4
			mov.w #arrayRef, r5
			mov.w #10000,r6 ;karsilastiracagimiz sayiyi belirleyelim

loopchk		cmp.w r4,r5
			jz bitir ;eger array1den sonraki arrayin adresine geldiysek anliyoruz ki arrayimizdeki tum elemanlari karsilastirmaya tabi tutmusuz ve bitiriyoruz
			cmp.w @r4+,r6
			jn buldum ;eger negatif flagi 1 olduysa 10000den buyuk sayi yakalamisizdir
			jmp loopchk ;eger yakalayamadiysak denemeye devam

buldum		inc r9
			jmp loopchk

bitir		jmp main2


;3 – Create a 20 byte-long uninitialized section in the memory (use .bss).
;4 – Fill the buffer created in step 3 with even numbers starting from 2. Numbers will be stored as words.

main2		mov.w #2,r10 ;ilk numberi register et
			mov.w #section1,r11
			mov.w #sectionRef,r12

loopchk2	cmp.w r11,r12
			jz bitir2 ;sonraki sectionin adresine geldiysek bitiriyortuz
			mov.w r10,0(r11) ;sayiyi tasi
			incd r11 ;adresi bir word increment et
			incd r10 ;bir sonraki cift sayiya gecmek icin 2 ile topla
			jmp loopchk2 ;loopu yinele

bitir2		jmp $ ;kodu cortlat
                                            

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
            
