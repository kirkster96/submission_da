#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>




int main (void)
{
	DDRB |= (1<<2);//PB5 as output
	PORTB |= (1<<2);//PB5 as output	
	
	EIMSK = (1<<INT0);
	sei();
	
	while (1)
	{
		PORTB |= (1<<2);//PB5 as output
	}
}	


ISR (INT0_vect)
{
	PORTB &= ~(1<<2);
	_delay_ms(1330);
}