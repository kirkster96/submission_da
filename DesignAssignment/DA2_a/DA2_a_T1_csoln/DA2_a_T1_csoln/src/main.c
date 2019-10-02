#define F_CPU 16000000UL

#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();

	DDRB |= (1<<3); //output PB3
	PORTB |= (0<<3);//output PB3 set to zero initial
	
	while(1){
		PORTB |= (1<<2); //output PB2 on
		_delay_ms(250);
		PORTB &= ~(1<<2); // off*/
		_delay_ms(375);	
			}
	

			return 1;
			}


