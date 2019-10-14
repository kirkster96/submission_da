#define F_CPU 16000000UL

#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{

	board_init();

	/* Insert application code here, after the board has been initialized. */
	
	DDRB |= (1<<DDB3); //output PB3
	TCCR0A = 0;//NORMAL OPERATION
	TCNT0=0x06;
	//START THE TIMER
	TCCR0B |= (1<<CS02)|(1<<CS00);
	//set prescaler to 64 and start the timer
		

		
	while(1){
	
		for(int j = 0; j < 1000; j++){
		for(int i =0; i<625; i++){
		while((TIFR0 & 0x01) == 0);
		}
		}
		PORTB ^= (1<<DDB3); //output PB2 on

		TCNT0=0x06;
		TIFR0=0x01;//reset the overflow flag
		}
		

		return 1;
}
