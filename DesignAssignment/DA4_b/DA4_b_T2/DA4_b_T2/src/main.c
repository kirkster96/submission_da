
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALE (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>


int main (void)
{
		//configure the PWM
		//use mode 14 PWM timer 1 for more accurate Freq. OCR0A is top value. OCR0B is duty cycle
		DDRB |= (1<<DDB1)|(1<<DDB2); //PB1 PB2 is now a output
		ICR1 = 0x9C3F;
		OCR1A = 0x0FA0;//set PWM for DUTY;
		
		//set non-inverting mode
		TCCR1A |= (1<<COM1A1)|(1<<COM1B1);
		
		//set mode 14
		TCCR1A |= (1<<WGM11);
		TCCR1B |= (1<<WGM13)|(1<<WGM12);
		
		//Set Prescale is 8		
		TCCR1B |=(1<<CS11);
		
		//initialize the ADC
		ADMUX = (0<<REFS1)|	//Reference selection bits
		(1<<REFS0)|			//AVcc - external cap at AREF
		(0<<ADLAR)|			//Left adjust most significant bit
		(0<<MUX2)|			//Analog channel selection bits
		(0<<MUX1)|			//ADC0 (PC0 PIN23)
		(0<<MUX0);
		ADCSRA = (1<<ADEN)|	//	Enable ADC
		(0<<ADSC)|			//ADC start conversion
		(0<<ADATE)|			//ADC Autotrigger enable
		(0<<ADIF)|			//ADC Interrupt Flag
		(0<<ADIE)|			//ADC Interrupt Enable
		(1<<ADPS2)|			//ADC prescaler bits
		(0<<ADPS1)|
		(1<<ADPS0);

		//PC0 as input for ADC conversion Pot value
		PORTC |= (1<<0);
		
		volatile unsigned char TEMP [4];
		
		while(1){
			ADCSRA |= (1<<ADSC);			//start conversion
			while((ADCSRA&(1<<ADIF))==0);	//wait for conversion to complete
			
			ADCSRA |= (1<<ADIF);
						
			
			int c = ADCL;
			c = c | (ADCH<<8);
			c = (c/1024.0)*5000/10;


			c =  200.0*(1.0-(c/499.0)) + (4000.0)*(c/499.0);

			//OCR1A = 0x0FA0 -> Duty Cycle  10% 
			//OCR1A = 0x00C8 -> Duty Cycle  5%

			OCR1A = c;
			
			
		}
}



