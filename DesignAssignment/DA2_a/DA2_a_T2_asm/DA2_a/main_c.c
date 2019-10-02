#include <avr/io.h>

#define F_CPU 16000000UL

#include<util/delay.h>


int main(void){

DDRB |= (1<<PB2);
DDRC |= (1<<PC3);
PORTC |= (1<<PC3);

while(1){

	if(PINC == 1){}
	PORTB |= (1<<PB2);
	_delay_ms(1330);
	PORTB &= ~(1<<PB2);
}

return 1;
}



}