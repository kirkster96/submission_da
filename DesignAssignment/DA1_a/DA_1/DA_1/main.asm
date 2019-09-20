;
; DA_1.asm
;
; Created: 9/19/2019 7:49:40 PM
; Author : Kirks
;
;R25:R24 hold the 16-bit multiplicand, R23:R22 hold 16-bit multiplier, and R20:R19:R18:R17 should hold the result.
.include <m328pdef.inc>

.EQU MYLOC = 0x200


.ORG 0
		LDI R16,0x00

		LDI R24,0x53 ;lower multiplicand
		LDI R25,0x41 ;upper multiplicand


		LDI R22,0x00 ;lower multiplier
		LDI R23,0x34 ;upper multiplier
loop:
		CP R22,R16
		BREQ reload	;dec LSB from upper multiplier and set lower multiplier to 0xFF
		SUBI R22,0b1
loopb:
		ADD R17,R24	;add lower to lowest answer
		ADC R18,R25	;add upper to 2nd lowest answer, include the carry from the lowest addition
		ADC R19,R16	;add the next register with zero and the carry from the most recent addition
		ADC R20,R16 ;add the next register with zero and the carry from the most recent addition

		JMP loop	;loop to check if done

reload:
		CP R23,R16
		BREQ done	;compare with zero, this means [R23,R22] is all zero and we are done
		DEC R23
		LDI R22, 0xFF
		JMP loopb	;branch to adding another multiplicand to the answer for this decrement
done:

NEXT: JMP NEXT