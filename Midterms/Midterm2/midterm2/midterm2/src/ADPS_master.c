/*
 * ADPS_master.c
 *
 * Created: 12/12/2019 8:26:30 PM
 *  Author: Kirks
 */ 

#ifndef  F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "ADPS_master.h"
#include "i2cmaster.h"



void init_uart(uint16_t baudrate){

	uint16_t UBRR_val = (F_CPU/16)/(baudrate-1);

	UBRR0H = UBRR_val >> 8;
	UBRR0L = UBRR_val;

	UCSR0B |= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0); // UART TX (Transmit - senden) einschalten
	UCSR0C |= (1<<USBS0) | (3<<UCSZ00); //Modus Asynchron 8N1 (8 Datenbits, No Parity, 1 Stopbit)
}

void uart_putc(unsigned char c){

	while(!(UCSR0A & (1<<UDRE0))); // wait until sending is possible
	UDR0 = c; // output character saved in c
}

void uart_puts(char *s){
	while(*s){
		uart_putc(*s);
		s++;
	}
}




void init_APDS9960(void){
	_delay_ms(150);										/* Power up time >100ms */
	i2c_start(APDS9960_WRITE);
	i2c_write(0x80); // set pointer to ENABLE REGISTER
	i2c_write(0x03); // write 0x06 to ENABLE REGISTER
	i2c_stop();

	i2c_start(APDS9960_WRITE);
	i2c_write(0x81); // set pointer to ALS ADC Integration Time
	i2c_write(0xDB); // 219 =0XDB = 37 = 103 ms = 37889
	i2c_stop();

	i2c_start(APDS9960_WRITE);
	i2c_write(0x8F); // set pointer to CONTROL<AGAIN>
	i2c_write(0x01); // ALS and Color Gain Control = 0 = x1
	i2c_stop();
}

