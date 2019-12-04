/**
 * \DA3_a Cameron Kirk
 *
 * \This is a AVR C program that will use the LM35 to print temperatur to the terminal
 *
 */

#define F_CPU 16000000UL
#define BAUD_RATE 9600

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

void usart_init ();
void usart_send (unsigned char ch);
void usart_print (char* str);



int main (void)
{
	//initialize the usart
	usart_init ();
	
	ADMUX = (0<<REFS1)|	//Reference selection bits
	(1<<REFS0)|			//AVcc - external cap at AREF
	(0<<ADLAR)|			//Left adjust most significant bit
	(1<<MUX2)|			//Analog channel selection bits
	(0<<MUX1)|			//ADC4 (PC4 PIN27)
	(0<<MUX0);
	ADCSRA = (1<<ADEN)|	//	Enable ADC
	(0<<ADSC)|			//ADC start conversion
	(0<<ADATE)|			//ADC Autotrigger enable
	(0<<ADIF)|			//ADC Interrupt Flag
	(0<<ADIE)|			//ADC Interrupt Enable
	(1<<ADPS2)|			//ADC prescaler bits
	(0<<ADPS1)|
	(1<<ADPS0);
		
	
	while (1){
		ADCSRA |= (1<<ADSC);			//start conversion
		while((ADCSRA&(1<<ADIF))==0);	//wait for conversion to complete 
		
		ADCSRA |= (1<<ADIF);
		
		int c = ADCL;
		c = c | (ADCH<<8);
		c = (c/1024.0)*5000/10;
		usart_send((c/100) + '0');
		c = c % 100;
		usart_send((c/10) + '0');
		c = c % 10;
		usart_send((c) + '0');
		usart_send('\r');
		
		_delay_ms(100);

		
		
	}
	return 0;
	
}

void usart_init(void){
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0L = F_CPU/16/BAUD_RATE-1;	
}

void usart_send( unsigned char ch){
	while(! (UCSR0A & (1<<UDRE0)));	//wait until UDR0 is empty
	UDR0 = ch;		//transmit ch
}
	

void usart_print(char* str){
	int i = 0;
	while(str[i] != 0){
		usart_send(str[i]);
		i++;
	}
}
