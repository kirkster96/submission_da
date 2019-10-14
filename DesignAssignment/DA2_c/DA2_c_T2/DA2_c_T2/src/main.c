//#define F_CPU 16000000UL

#include <asf.h>
#include <avr/io.h>
//#include <util/delay.h>
#include <avr/interrupt.h>

int OFcount = 0;

int main (void)
{

	board_init();

	DDRB |= (1<<DDB3); //output PB3

	TCNT0=0x00;//timer|count register
	TCCR0A = 0x00;//configuration register NORMAL MODE
	TCCR0B |= (1<<CS01)|(1<<CS00); //configuration register
	//PRESCALER 64
	
	
	TIMSK0 |= (1 << TOIE0);//enable timer0 overflow interrupt
	sei();
	//START THE TIMER

	//set prescaler to 64 and start the timer
	

	
	while(1){
		//MAIN LOOP
	}
}

ISR (TIMER0_OVF_vect)
{
	OFcount++;
	if (OFcount == 625)
	{
		PORTB ^= (1<<DDB3); //output PB3 on
		OFcount = 0;
	}
}

