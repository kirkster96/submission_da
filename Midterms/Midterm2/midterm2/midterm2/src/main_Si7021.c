/*
 * Sensor_ATMega328P.c
 *
 * Created: 4/7/2019 1:38:54 PM
 * Author : VenkatesanMuthukumar
 */ 

#define F_CPU 16000000UL			/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>					/* Include AVR std. library file */
#include <util/delay.h>				/* Include delay header file */
#include <inttypes.h>				/* Include integer type header file */
#include <stdlib.h>					/* Include standard library file */
#include <stdio.h>					/* Include standard library file */
#include <avr/interrupt.h>			/* Include avr interrupt header file */
#include <util/twi.h>

#include "main_Si7021.h"
#include "i2cmaster.h"
#include "uart.h"					/* Include USART header file */

unsigned char ret;        // return value



void Si7021_writereg(uint8_t reg, uint8_t val)
{
	i2c_start(Si7021+I2C_WRITE);
	i2c_write(reg);  // go to register e.g. 106 user control
	i2c_write(val);  // set value e.g. to 0100 0000 FIFO enable
	i2c_stop();      // set stop condition = release bus
}




void Init_Si7021()
{


	ret = i2c_start(Si7021+I2C_WRITE);       // set device address and write mode
	if ( ret )
	{
		/* failed to issue start condition, possibly no device found */
		i2c_stop();
		//red_led(1);    // Turn on the red LED immediately to signal the read is not ok
		while(1) {;;}  // lock program here as sensor init failed
	}
	else
	{
	}
}

void Si7021_config(void)
{
	Si7021_writereg(Si7021_Write_Heater_Control_Register, 0x09);
	Si7021_writereg(Si7021_Write_Config_Register, (Si7021_Config_Resolution_RH_12_T14 | Si70211_Config_Heater_On));
	_delay_ms(900);
	Si7021_writereg(Si7021_Write_Heater_Control_Register, 0x00);
	Si7021_writereg(Si7021_Write_Config_Register, (Si7021_Config_Resolution_RH_12_T14 | Si70211_Config_Heater_Off));
	_delay_ms(900);
}
/*
int main(void)
{
	char buffer[30], float_[5];
    USART_Init(9600);
	sei();             // Enable global interrupts

	Init_Si7021();    // Sensor init
	Si7021_config();
	_delay_ms(200);     // Wait for 200 ms.

	while (1)
	{
	TMP_Data = Si7021_readreg(0xE3);   // read ch0 LSB byte
	CTMP_Data = 175.25f * TMP_Data / 65536.0f - 46.85f;
	dtostrf( CTMP_Data, 3, 2, float_ );					
	sprintf(buffer," Temperature = %s C\n",float_);
	USART_SendString(buffer);
	_delay_ms(2000);     // Wait for 2000 ms.
	}
}
*/