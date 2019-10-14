#define F_CPU 16000000UL
#include <asf.h>
#include <avr/io.h>
#include <avr/interrupt.h>


int OFcount = 0;

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();

	DDRB |= (1<<DDB3); //output PB3

	OCR0A = 0x62;
	TCNT0 = 0;
	
	TCCR0A = (1<<WGM01);//configuration register CTC MODE
	TCCR0B |= (1<<CS01)|(1<<CS00); //configuration register
	//PRESCALER 64
		
	TIMSK0 |= (1 << OCIE0A);//enable timer0 overflow interrupt
	sei();
	//START THE TIMER

	//set prescaler to 64 and start the timer
	

	
	while(1){
		//MAIN LOOP
	}
}

ISR (TIMER0_COMPA_vect)
{
	OFcount++;
	if (OFcount == 1000)
	{
		PORTB ^= (1<<DDB3); //output PB3 on
		OFcount = 0;
	}
	//PORTB ^= (1<<DDB3); //output PB3 on

	TIFR0 |= (1<<OCF0A);
}

