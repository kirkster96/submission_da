;
; DA2_a_T1_asm.asm
;
; Created: 10/2/2019 8:46:30 AM
; Author : Kirks
;


; Design a delay subroutine to generate a waveform on PORTB.3 with 40% DC and 0.625 sec period.
;0.25 sec delay. 16MHz clock. 0.0625us/instruction. 4000000 instructions where signal will be high
;6000000 instructions will be low



	SBI DDRB,3



start:
		CBi PortB,3
ldi R19,50     ; cycle = 1
delay3:  ldi R20,255    ;cycle = 1 * 50
nop					   ;cycle = 1 * 50 *255
delay4:  ldi R21,154    ;cycle = 1 * 50 * 255
nop					   ;cycle = 1 * 50 * 255 * 255	
nop					   ;cycle = 1 * 50 * 255 * 255	
nop					   ;cycle = 1 * 50 * 255 * 255	
nop					   ;cycle = 1 * 50 * 255 * 255	
nop
nop					   ;cycle = 1 * 50 * 255 * 255	
delay5:  dec R21        ;cycle = 1 * 50 * 255 * 255	
brne delay5     ;cycle = 2/1 * 50 * 255 * 255 => 50*255(254*2)+50*255(1*1)
dec R20        ;cycle = 1 * 50 * 255
brne delay4     ;cycle = 2/1 * 50 * 255=> 50(254*2)+105(1*1)
dec R19        ;cycle = 1 * 50 * 255
nop
nop
brne delay3     ;cycle = 2/1 * 50 => (49*2)+(1*1)

		SBI  PORTB,3


ldi R19,50     ; cycle = 1
delay0:  ldi R20,255    ;cycle = 1 * 50
nop					   ;cycle = 1 * 50 *255
delay1:  ldi R21,102    ;cycle = 1 * 50 * 255
nop					   ;cycle = 1 * 50 * 255 * 255	
nop					   ;cycle = 1 * 50 * 255 * 255	
nop					   ;cycle = 1 * 50 * 255 * 255	
nop					   ;cycle = 1 * 50 * 255 * 255	
nop					   ;cycle = 1 * 50 * 255 * 255	
delay2:  dec R21        ;cycle = 1 * 50 * 255 * 255	
brne delay2     ;cycle = 2/1 * 50 * 255 * 255 => 50*255(254*2)+50*255(1*1)
dec R20        ;cycle = 1 * 50 * 255
nop
brne delay1     ;cycle = 2/1 * 50 * 255=> 50(254*2)+105(1*1)
dec R19        ;cycle = 1 * 50 * 255
nop
nop
nop
brne delay0     ;cycle = 2/1 * 50 => (49*2)+(1*1)

    jmp start
