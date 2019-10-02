;
; DA2_a.asm
;
; Created: 9/30/2019 10:07:47 PM
; Author : Kirks
;
.INCLUDE "M328PBDEF.INC" 

JMP start


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

start:
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
AGAIN: SBIC PINC,3;skip next if PC is clear
	RJMP OVER;(JMP is OK too)
	CBi PortB,2
	call DelaySubroutine
	RJMP AGAIN;we can use JMP too
OVER:  SBI  PORTB,2
	RJMP AGAIN;we can use JMP too





