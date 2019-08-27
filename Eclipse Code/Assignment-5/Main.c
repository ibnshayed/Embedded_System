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

int main(void) {
	DDRB &= 0x00; //Set as input
	DDRD = 0xFF; // set as output
	PORTD = 0x00;
	int count = 0;
	while (1) {

		if (bit_is_set(PINB, PINB5)) {
			_delay_ms(20);
			count++;
			_delay_ms(20);
		}

		if (bit_is_set(PINB, PINB5)) {
			_delay_ms(20);
			count++;
			_delay_ms(50);
		}
		if (bit_is_set(PINB, PINB5)) {
			_delay_ms(20);
			count++;
			_delay_ms(50);
		}
		//Skip Backward -- Three times quickly
		else if (count == 3) {
			PORTD |= _BV(PORTD2);
			_delay_ms(100);
			PORTD &= 0x00;
			count = 0;
		}
		//Fast Forward -- Twice quickly and hold the second press
		if (count >= 2 && bit_is_set(PINB, PINB5)) {
			PORTD |= _BV(PORTD3);
			_delay_ms(100);
			PORTD &= 0x00;
			count = 0;
		}
		//Skip Forward -- Twice qickly
		else if (count == 2) {
			PORTD |= _BV(PORTD1);
			_delay_ms(100);
			PORTD &= 0x00;
			count = 0;
		}
		//Play/Pause -- Press the multi-Function Button
		else if (count == 1) {
			if (bit_is_clear(PIND, PIND0))
				PORTD |= _BV(PORTD0);
			else
				PORTD = 0x00;
			_delay_ms(100);

			count = 0;
		}

	}
}

