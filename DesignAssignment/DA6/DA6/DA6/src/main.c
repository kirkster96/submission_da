/**
 * \DA3_a Cameron Kirk
 *
 * \This is a AVR C program that will use the LM35 to print temperatur to the terminal
 *
 */

#define F_CPU 16000000UL
#define I2C_SCL_CLOCK 100000L
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
	
	//initialize the TWI for I2C
	TWBR0 = ((F_CPU/I2C_SCL_CLOCK)-16)/2; //set module clock freq.
	TWCR0 |= (1<<TWEN); //enable the TWI module
	
	//Set port
	
	volatile unsigned char TEMP [4];
	while (1){
	
		UART_sendString(TEMP);
		_delay_ms(2000);
		UART_sendString("\r\n\r\n");	
		
	}
	return 0;
	
}


void I2C_Start_Wait(int value)
{
	// send the START condition
	TWCR0 |= (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while((TWCR0 & (1 << TWINT)) == 0);
}

void I2C_WAIT_CLEAR(int a, int b)
{
	while((TWCR0 & (1 << TWINT)) == 0);
}

void I2C_Write(int value)
{
	//Send device address
	TWDR0 |= value;
	TWCR0 |= (1<<TWINT)|(1<<TWEN);
	//wait until transmission completed and ACK/NACK has been recieved
	while	((TWCR0 & (1<<TWINT)) == 0);

}

void I2C_Stop()
{
	TWCR0 |= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

}

unsigned char I2C_Read(unsigned char isLast){

	if (isLast == 0)
		TWCR0 |= (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	else
		TWCR0 |= (1<<TWINT)|(1<<TWEN);
	while	((TWCR0 & (1<<TWINT)) == 0);
	
	return TWDR0;
}

void MPU6050_Init ()/* Gyro initialization function*/
{
int INT_ENABLE;
int GYRO_CONFIG;
int CONFIG;
int PWR_MGMT_1;
int SMPLRT_DIV;
_delay_ms ( 150);/* Power up time >100ms*/
I2C_Start_Wait(0xD0);/* Start with device write address*/
I2C_Write(SMPLRT_DIV);/* Write to sample rate register*/
I2C_Write(0x07);/* 1KHz sample rate*/
	I2C_Stop();

I2C_Start_Wait(0xD0);
I2C_Write(PWR_MGMT_1);/* Write to power management register*/
I2C_Write(0x01);/* X axis gyroscope reference frequency*/
I2C_Stop();

I2C_Start_Wait(0xD0);
I2C_Write(CONFIG);/* Write to Configuration register*/
I2C_Write(0x00);/* Fs = 8KHz*/
I2C_Stop();

I2C_Start_Wait(0xD0);
I2C_Write(GYRO_CONFIG);/* Write to Gyro configuration register*/
I2C_Write(0x18);/* Full scale range 2000 degree/C */
I2C_Stop();

I2C_Start_Wait(0xD0);
I2C_Write(INT_ENABLE);/* Write to interrupt enable register*/
I2C_Write(0x01);
I2C_Stop();
}

void I2C_Start(void)
{
		// send the START condition
		TWCR0 |= (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
		while((TWCR0 & (1 << TWINT)) == 0);	
}

/*
void MPU6050_writereg(uint8_t reg, uint8_t val){
	I2C_Start(MPU6050+I2C_Write);
	I2C_Write(reg);//go to register
	I2C_Write(val);//set value
	I2C_Stop();//set stop condition = bus release	
}

uint8_t MPU6050_readreg(uint8_t reg){
	I2C_Start_Wait(MPU6050+I2C_Write);
	I2C_Write(reg);
	I2C_rep_start(MPU6050+I2C_Read);
	raw = I2C_ReadACK();
	raw = (raw<<8)|i2creadNAK();
	I2C_Stop();
	
	return raw;
}*/

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
	
void UART_sendString(const char *str){
	
	while(*str){
		usart_send(*str++);
		}
			
}
