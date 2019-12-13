/**
 * \DA3_a Cameron Kirk
 *
 * \This is a AVR C program that will use the LM35 to print temperatur to the terminal
 *
 */

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALE (((F_CPU / (BAUD_RATE * 16UL))) - 1)
#define APDS9960_WRITE 0x72
#define APDS9960_READ 0x73


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
#include <APDS9960_def.h>
#include <i2cmaster.h>
#include <ADPS_master.h>
#include <math.h>
#include <main_Si7021.h>
#include <uart.h>
#include <inttypes.h>


void usart_init ();
void usart_send (char ch);
void UART_sendString(const char *str);
void check_OK();
void getreading(void);
uint16_t Si7021_readreg(uint8_t reg);


volatile unsigned char data_in[8];
volatile unsigned char command_in[8];

volatile unsigned char data_count;
volatile unsigned char command_ready;

char buffer[6];

int16_t raw_R = 0;
int16_t raw_G = 0;
int16_t raw_B = 0;
int16_t raw_C = 0;

uint16_t raw;             // raw sensor value
uint16_t HT_Data, CHT_Data;          // Humidity raw value
uint16_t TMP_Data, CTMP_Data;          // Temperature raw value
uint16_t PTMP_Data, CPTMP_Data;          // Temperature raw value


int main (void)
{
		char buffer[30], float_[5];
		
		//initialize the usart methods used by ASPD9906
		usart_init ();

		USART_Init(9600);
		i2c_init();     // init I2C interface
		_delay_ms(200);  // Wait for 200 ms.
		
		Init_Si7021();
		_delay_ms(200);     // Wait for 200 ms.
				
		Si7021_config();
		_delay_ms(200);     // Wait for 200 ms.
			
		init_APDS9960();
		_delay_ms(200);     // Wait for 200 ms.


		UART_sendString("AT\r\n");
		_delay_ms(3000);
		check_OK();
		// Select WIFI mode
		UART_sendString("AT+CWMODE=1\r\n");
		_delay_ms(3000);
		// Connect to local WIFI
		UART_sendString("AT+CWJAP=\"Samsung Galaxy Note9 7157\",\"Cameronkirk1\"\r\n");
		_delay_ms(3000);
		// Enable connection
		UART_sendString("AT+CIPMUX=0\r\n");
		_delay_ms(3000);


		while (1)
		{
			TMP_Data = Si7021_readreg(0xE3);   // read ch0 LSB byte
			CTMP_Data = 175.25f * TMP_Data / 65536.0f - 46.85f;
			dtostrf( CTMP_Data, 3, 2, float_ );
			sprintf(buffer," Temperature = %s C\n",float_);
			
			// Start a connection as client to Thingspeak
			UART_sendString("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
			_delay_ms(2000);
			// Specify the size of the data
			UART_sendString("AT+CIPSEND=45\r\n");
			_delay_ms(2000);
			// Send temperature
			UART_sendString("GET /update?key=U1KZD3KPYBFH5DIZ&field1=");
			_delay_ms(2000);
			UART_sendString(buffer);
			_delay_ms(2000);
			UART_sendString("\r\n\r\n");
			
			_delay_ms(2000);     // Wait for 2000 ms.
			
			getreading();
			
			itoa(raw_C, buffer, 10);
			// Start a connection as client to Thingspeak
			UART_sendString("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
			_delay_ms(2000);
			// Specify the size of the data
			UART_sendString("AT+CIPSEND=45\r\n");
			_delay_ms(2000);
			// Send temperature
			UART_sendString("GET /update?key=U1KZD3KPYBFH5DIZ&field2=");
			_delay_ms(2000);
			UART_sendString(buffer);
			_delay_ms(2000);
			UART_sendString("\r\n\r\n");

			
			itoa(raw_R, buffer, 10);
			// Start a connection as client to Thingspeak
			UART_sendString("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
			_delay_ms(2000);
			// Specify the size of the data
			UART_sendString("AT+CIPSEND=45\r\n");
			_delay_ms(2000);
			// Send temperature
			UART_sendString("GET /update?key=U1KZD3KPYBFH5DIZ&field3=");
			_delay_ms(2000);
			UART_sendString(buffer);
			_delay_ms(2000);
			UART_sendString("\r\n\r\n");

			
			itoa(raw_G, buffer, 10);
			// Start a connection as client to Thingspeak
			UART_sendString("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
			_delay_ms(2000);
			// Specify the size of the data
			UART_sendString("AT+CIPSEND=45\r\n");
			_delay_ms(2000);
			// Send temperature
			UART_sendString("GET /update?key=U1KZD3KPYBFH5DIZ&field4=");
			_delay_ms(2000);
			UART_sendString(buffer);
			_delay_ms(2000);
			UART_sendString("\r\n\r\n");

			
			itoa(raw_B, buffer, 10);
			// Start a connection as client to Thingspeak
			UART_sendString("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
			_delay_ms(2000);
			// Specify the size of the data
			UART_sendString("AT+CIPSEND=45\r\n");
			_delay_ms(2000);
			// Send temperature
			UART_sendString("GET /update?key=U1KZD3KPYBFH5DIZ&field5=");
			_delay_ms(2000);
			UART_sendString(buffer);
			_delay_ms(2000);
			UART_sendString("\r\n\r\n");

			
			_delay_ms(1000);
		}
	

	
	
	
	
	
	/*
	//LM35 ADC configuration
	
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
	
	
	
	
	//MIDTERM 1 CODE
	

		
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
	*/
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


void getreading(void){

	i2c_start(APDS9960_WRITE);
	i2c_write(0x94); // set pointer to CDATA
	i2c_stop();

	i2c_start(APDS9960_READ);

	raw_C =  ((uint8_t)i2c_readAck());
	raw_C |= ((uint8_t)i2c_readAck())<<8;

	raw_R = ((uint8_t)i2c_readAck());
	raw_R |= ((uint8_t)i2c_readAck())<<8;

	raw_G = ((uint8_t)i2c_readAck());
	raw_G |= ((uint8_t)i2c_readAck())<<8;

	raw_B = ((uint8_t)i2c_readAck());
	raw_B |= ((uint8_t)i2c_readAck())<<8;

	i2c_stop();

}

uint16_t Si7021_readreg(uint8_t reg)
{
	i2c_start_wait(Si7021+I2C_WRITE);  // set device address and write mode
	i2c_write(reg);                     // ACCEL_XOUT
	i2c_write(0x81);                     // ACCEL_XOUT
	i2c_rep_start(Si7021+I2C_READ);    // set device address and read mode
	raw = i2c_readAck();                // read one intermediate byte
	raw = (raw<<8) | i2c_readNak();     // read last byte
	i2c_stop();
	return raw;
}

