/*
 * Main.c
 *
 *  Created on: Aug 6, 2019
 *      Author: ibnshayed
 */
/*Button*/
#include <avr/io.h>
#include <avr/delay.h>
#define F_CPU 16000000UL

void play_or_pause(int count) {
	if (count == 1) {
		PORTD |= _BV(PORTD0);
		_delay_ms(10);
	}

	else{
		PORTD &= ~_BV(PORTD0);
	}
}

int main(void) {
	DDRB &= ~_BV(DDB5); //Set as input
	DDRD = 0xFF; // set as output
	PORTD = 0x00;
	int count = 0;

	while (1) {
		if (bit_is_set(PINB, PINB5)) {
			count++;
		}

		play_or_pause(count);

		if(count > 1)
			count = 0;
	}

}

