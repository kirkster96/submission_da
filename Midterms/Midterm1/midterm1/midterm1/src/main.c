/**
 * \DA3_a Cameron Kirk
 *
 * \This is a AVR C program that will use the LM35 to print temperatur to the terminal
 *
 */

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALE (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#define TRUE 1
#define FALSE 0

#define  CHAR_NEWLINE '\n'
#define  CHAR_RETURN '\r'
#define  RETURN_NEWLINE "\r\n"


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void usart_init ();
void usart_send (char ch);
void UART_sendString(const char *str);
void check_OK();

volatile unsigned char data_in[8];
volatile unsigned char command_in[8];

volatile unsigned char data_count;
volatile unsigned char command_ready;


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
	
	UART_sendString("AT\r\n");
		_delay_ms(3000);
	check_OK();
	// Select WIFI mode
	UART_sendString("AT+CWMODE=1\r\n");
	_delay_ms(3000);
	// Connect to local WIFI
	UART_sendString("AT+CWJAP=\"_-_-\",\"_-_-_\"\r\n");
	_delay_ms(3000);
	// Enable connection
	UART_sendString("AT+CIPMUX=0\r\n");
	_delay_ms(3000);
		
	volatile unsigned char TEMP [4];
	while (1){
		ADCSRA |= (1<<ADSC);			//start conversion
		while((ADCSRA&(1<<ADIF))==0);	//wait for conversion to complete 
		
		ADCSRA |= (1<<ADIF);
		
		
		
		int c = ADCL;
		c = c | (ADCH<<8);
		c = (c/1024.0)*5000/10;
		
		itoa(c,TEMP,10);

		
		
		// Start a connection as client to Thingspeak
		UART_sendString("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
		_delay_ms(2000);
		// Specify the size of the data
		UART_sendString("AT+CIPSEND=45\r\n");
		_delay_ms(2000);
		// Send temperature
		UART_sendString("GET /update?key=2NB8QCW9WK5PJNS9&field1=");
		_delay_ms(2000);
		UART_sendString(TEMP);
		_delay_ms(2000);
		UART_sendString("\r\n\r\n");

		
		_delay_ms(15000);

		
		
	}
	return 0;
	
}

void usart_init(void){
	//turn on Rx, TX
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	//8bit char sizes
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	//set baud rate
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;
	//Enable the USART Receive interrupt
	UCSR0B |= (1<<RXCIE0);
	
	//globally enable interrupts
	//sei();
	
}

void usart_send(char ch){
	while(! (UCSR0A & (1<<UDRE0)));	//wait until UDR0 is empty
	UDR0 = ch;		//transmit ch
}

	
void check_OK(){
		volatile unsigned char i;
		volatile unsigned char result[2];
		int k = 0;	
		
		/*
		// Wait for the response to finish
		while(result != "OK"){
			while(!(UCSR0A & (1<<RXC0)));
			i = UDR0;
			usart_send(i);
			result[(k%2)]=i;
			k++;
		}

	*/
		
	}
	
void UART_sendString(const char *str){
	
	while(*str){
		usart_send(*str++);
		}
			
}

