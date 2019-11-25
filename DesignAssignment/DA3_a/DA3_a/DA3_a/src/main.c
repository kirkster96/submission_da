/**
 * \DA3_a Cameron Kirk
 *
 * \This is a AVR C program that will display a string, random integer, and random float to the serial terminal every 1 sec
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
	
	
	//allocate char arrays
	char * textString ="Hello";
	char * textInt = "0";
	char * textFloat = "0";
	
	while (1){
		//generate random numbers to display on serial terminal
		int a = rand();
		double b = ((double)rand())/((double)rand());
		
		//display string and line feed
		usart_print(textString);
		usart_send('\r');
			
		//display integer and line feed
		itoa(a,textInt,10);
		usart_print(textInt);
		usart_send('\r');
		
		//display float and linefeed
		dtostrf(b,3,3,textFloat);
		usart_print(textInt);
		usart_send('\r');
		
		_delay_ms(1000);		
		
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
