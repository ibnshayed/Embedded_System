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
int count = 0;
int volMin = 0;
int volMax = 100;
int volume = 0;

void PINB0_play_pause(uint8_t pin) {
	if (bit_is_set(PINB, pin)) {
		PORTD ^= _BV(PORTD0);
		_delay_ms(20);
	}

}
void PINB1_skip_forward(uint8_t pin) {

	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(20);
	}

	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(50);
	}
	if (count == 2) {
		PORTD |= _BV(PORTD1);
		_delay_ms(100);
		PORTD &= ~_BV(PORTD1);
		count = 0;
	}

}
void PINB2_skip_backward(uint8_t pin) {
	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(20);
	}

	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(50);
	}
	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(50);
	}
	if (count == 3) {
		PORTD |= _BV(PORTD2);
		_delay_ms(100);
		PORTD &= ~_BV(PORTD2);
		count = 0;
	}

}
void PINB3_fast_forward(uint8_t pin) {
	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(20);
	}

	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(50);
	}
	if (count >= 2 && bit_is_set(PINB, pin)) {
		PORTD |= _BV(PORTD3);

	} else {
		_delay_ms(100);
		PORTD &= ~_BV(PORTD3);
		count = 0;
	}

}
void PINB4_rewind(uint8_t pin) {
	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(20);
	}

	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(50);
	}
	if (bit_is_set(PINB, pin)) {
		_delay_ms(20);
		count++;
		_delay_ms(20);
	}

	if (count >= 3 && bit_is_set(PINB, pin)) {
		PORTD |= _BV(PORTD4);
	}
	else {
			_delay_ms(100);
			PORTD &= ~_BV(PORTD4);
			count = 0;
		}

}

void PINB5_volumeUp(uint8_t pin) {
	if (bit_is_set(PINB, pin)) {
		PORTD |= _BV(PORTD5);
		volume = volume_counter(volume + 1);
		_delay_ms(200);
		PORTD &= ~_BV(PORTD5);

	}
}
void PINB6_volumeDown(uint8_t pin) {
	if (bit_is_set(PINB, pin)) {
		PORTD |= _BV(PORTD6);
		volume = volume_counter(volume - 1);
		_delay_ms(200);
		PORTD &= ~_BV(PORTD6);

	}
}

int volume_counter(int vol) {
	if (vol < volMin)
		return volMin;
	if (vol > volMax)
		return volMax;
	else
		return vol;
}

int main(void) {
	DDRB &= 0x00; //Set as input
	DDRD = 0xFF; // set as output
	PORTD = 0x00;
	//int count = 0;
	while (1) {

		//Press the Multi-function button
		if (bit_is_set(PINB, PINB0)) {
			PINB0_play_pause(PINB0);
		}

		//Press twice quickly.
		if (bit_is_set(PINB, PINB1)) {
			PINB1_skip_forward(PINB1);
		}

		//Press three times quickly.
		if (bit_is_set(PINB, PINB2)) {
			PINB2_skip_backward(PINB2);
		}

		//Press twice quickly and hold the second press.
		if (bit_is_set(PINB, PINB3)) {
			PINB3_fast_forward(PINB3);
		}

		//Press three times quickly and hold the third press.
		if (bit_is_set(PINB, PINB4)) {
			PINB4_rewind(PINB4);
		}

		//Press onece
		if (bit_is_set(PINB, PINB5)) {
			PINB5_volumeUp(PINB5);
		}

		//Press onece
		if (bit_is_set(PINB, PINB6)) {
			PINB6_volumeDown(PINB6);
		}

	}
}

