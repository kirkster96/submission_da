;
; DA2_a.asm
;
; Created: 9/30/2019 10:07:47 PM
; Author : Kirks
;
.INCLUDE "M328PBDEF.INC" 

.ORG 0	;location for reset
	JMP main
.ORG 0x02	;location  for	EXT_INT0
	JMP EX0_ISR
	
main:
	;initialize the stack pointer
	LDI R20,HIGH(RAMEND)
	OUT SPH,R20
	LDI R20,LOW(RAMEND)
	OUT SPL,R20

	ldi r16,0x00
	out DDRB, r16
	out DDRC, r16
	out DDRD, r16
	out PortB,r16
	out PortD,r16
	out PortC,r16

	CBI  DDRC,3;make PC3 an input
	CBI  portC,3;make PC3 pull up resistor to active high

	SBI DDRB,2
	SBI  PORTB,2


	;LDI R20, 0x2 ;ENABLE INT0
	;OUT EICRA, R20
	LDI R20, 1<<INT0 ;ENABLE INT0
	OUT EIMSK, R20
	SEI

HERE: JMP HERE

EX0_ISR: LDI R20, 1<<INTF0
	OUT EIFR, R20
	CBi PortB,2
	call DelaySubroutine

	SBI  PORTB,2
	RETI

DelaySubroutine:
	ldi R19,108     ; cycle = 1
	delay0:  ldi R20,255    ;cycle = 1 * 108
	nop					   ;cycle = 1 * 108
	delay1:  ldi R21,255    ;cycle = 1 * 108 * 255
	nop					   ;cycle = 1 * 108 * 255
	nop					   ;cycle = 1 * 108 * 255
	nop					   ;cycle = 1 * 108 * 255
	nop					   ;cycle = 1 * 108 * 255
	nop					   ;cycle = 1 * 108 * 255
	delay2:  dec R21        ;cycle = 1 * 108 * 255 * 255	
	brne delay2     ;cycle = 2/1 * 108 * 255 * 255 => 105*255(254*2)+105*255(1*1)
	dec R20        ;cycle = 1 * 108 * 255
	brne delay1     ;cycle = 2/1 * 108 * 255=> 105(254*2)+105(1*1)
	dec R19        ;cycle = 1 * 108 * 255
	brne delay0     ;cycle = 2/1 * 108 * 255=> 105(254*2)+105(1*1)
	ret              ;cycle = 1

;1.33 sec delay. 16MHz clock. 0.0625us/instruction. 21280000 instructions is 1.33 seconds




