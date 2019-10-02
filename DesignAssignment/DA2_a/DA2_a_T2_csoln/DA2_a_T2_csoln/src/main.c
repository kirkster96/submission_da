/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#define F_CPU 16000000UL

#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();

	DDRB |= (1<<2); //output PB2
	PORTB |= (0<<2);//output PB2 set to zero initial
	 
	DDRC |= (0<<3); // PC3 input 
	PORTC |= (1<<3);// PC3 input pullup resistor enable

	while(1){

		
		if(PINC & (1<<3)){
		PORTB |= (1<<2); //output PB2 on
		}
		else if(PINC & (0<<3))
			break;
		else{
			_delay_ms(1330);
			PORTB &= ~(1<<2);} // off*/
	}

	return 1;
}




