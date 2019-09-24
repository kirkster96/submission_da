;
; DA_1B.asm
;
; Created: 9/23/2019 10:06:04 PM
; Author : Kirks
;

.include <m328pdef.inc>

.EQU STARTADDS = 0x0200


.ORG 0

		;load up pointers
		LDI XL,LOW(STARTADDS)
		LDI XH,HIGH(STARTADDS)

		LDI YL,LOW(0x0300)
		LDI YH,HIGH(0x0300)

		LDI ZL,LOW(0x0500)
		LDI ZH,HIGH(0x0500)

		;X starting address of 250 numbers
		;Y divisible by 5
		;Z else

		LDI R20,0x00 ;current number
		LDI R21,0xFA ;iterations
		LDI R22,0x00;

		;load 250 numbers into memory
loop:
		ST X+, R20
		INC R20
		DEC R21
		BRNE loop


		LDI R21,0xFB ;iterations
nextnum:
		DEC R21
		CP R21, R22
		BREQ done
		LD R20, -X
		CBR R20, 0xF8

		SUBI R20, 5
		BREQ divisible
		JMP notdiv

divisible:
		LD R20,X
		ST Y+,R20
		;running sum into R17:R16
		ADD R16,R20
		ADC	R17, R22
		JMP nextnum
	
notdiv:
		LD R20,X
		ST Z+,R20
		;running sum into R19:R18
		ADD R18,R20
		ADC	R19, R22
		JMP nextnum

done:

	



NEXT: JMP NEXT