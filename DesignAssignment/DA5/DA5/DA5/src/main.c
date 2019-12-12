/*
 * SPI_loopback.c
 *
 * Created: 2/25/2019 6:12:47 PM
 * Author : VenkatesanMuthukumar
 */

/* SPI Test program
 * Designed to be used with a jumper from MOSI to MISO for loopback test
 * uC is Atmel ATmega128
 */

#define F_CPU 16000000UL
/*
#define SPCR _SFR_IO8(0x2C)
#define SPSR _SFR_IO8(0x2D)
#define SPDR _SFR_IO8(0x2E)
*/

#define BAUD_RATE 9600
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>

#include <stdlib.h>


char SPI_transmit(char);
char SPI_receive(char);

void usart_init(void);
void usart_send(char ch);
void USART_putstring(char *StringPtr);

char data = 'a'; //0X41;
char ar[]= "hello";
int main() {

unsigned char rxdata, txdata;
  DDRB |= (1 << DDRB2) | (1 << DDRB3) | (1 << DDRB5); // SCK, MOSI and SS as outputs
  PORTB &= ~(1<<DDRB4);

  usart_init();
  
  SPSR0 |= (0 << SPI2X); // Doubled Clock Frequency: f_OSC / 2
 
 
  SPCR0 |= (1<<MSTR);
  SPCR0 |= (1<<SPR0)|(1<<SPR1);
  SPCR0 |= (1<<SPE);
  
  //setup ADC
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


 
 	char TEMP [4];
  while(1) {

	 
	 		ADCSRA |= (1<<ADSC);			//start conversion
	 		while((ADCSRA&(1<<ADIF))==0);	//wait for conversion to complete
	 		ADCSRA |= (1<<ADIF);
	 		
	 		
	 		
	 		int c = ADCL;
	 		c = c | (ADCH<<8);
	 		c = (c/1024.0)*5000/10;
	 		
	 		itoa(c,TEMP,10);
			 
			 for (int i = 0; i < strlen(TEMP); i++)
			 {

				rxdata=SPI_transmit(TEMP[i]);
				USART_putstring("TX Loopback Complete  ...   ");
				usart_send(rxdata);
				USART_putstring("    ");
				_delay_ms(1000);
				txdata = SPI_receive(TEMP[i]);
				usart_send(txdata);
				USART_putstring("    ..... RX Loopback Complete");
				USART_putstring("\n");
			 }

 
  }
  return 0;
}

void usart_init(void) {
  UCSR0B = (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UBRR0L = F_CPU / 16 / BAUD_RATE - 1;
}

void usart_send(char ch) {
  while (!(UCSR0A & (1 << UDRE0)))
    ;        // wait until UDR0 is empty
  UDR0 = ch; // transmit ch
}

void USART_putstring(char *StringPtr) {

  while (*StringPtr != 0x00) {
    usart_send(*StringPtr);
    StringPtr++;
  }
}

char SPI_transmit(char data) {
  // Start transmission
  SPDR0 = data;
  // Wait for transmission complete
  while (!(SPSR0 & (1 << SPIF)));
  data = SPDR0;
  return (data);
}

char SPI_receive(char data) {
  SPDR0 = data-32;
  while (!(SPSR0 & (1 << SPIF)));
  data = SPDR0;
  return data;
}

