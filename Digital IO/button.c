/*Button*/
#include <avr/io.h>
#include <avr/delay.h>

#define F_CPU 16000000UL

int main(void)
{
	DDRD &= ~_BV(DDD2); //Set as input
	DDRB |= _BV(DDB5); // set as output
	PORTB= 0x00;

	while(1)
	{
		if(bit_is_set(PIND,PIND2))
		{
			PORTB|= _BV(PORTB5);

		}
		else
		{
			PORTB &= ~_BV(PORTB5);
		}
	}

}
