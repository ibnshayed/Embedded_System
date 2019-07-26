/*
 * seven_segment.c
 *
 *  Created on: May 25, 2015
 *      Author: rezwan
 *  atmega328p driving a seven segment common cathode display. seven segment A-G is connected to portd 0-6 in order
 *  		G F E D C B A
 *   0 -> 	0 1 1 1 1 1 1
 *   1 ->	0 0 0 0 1 1 0
 *   2 ->	1 0 1 1 0 1 1
 *   3 ->	1 0 0 1 1 1 1
 *   4 ->	1 1 0 0 1 1 0
 *   5 ->	1 1 0 1 1 0 1
 *   6 ->	1 1 1 1 1 0 1
 *	 7 ->	0 0 0 0 1 1 1
 *	 8 ->	1 1 1 1 1 1 1
 *	 9 ->	1 1 0 1 1 1 1
 *	 A ->	1 1 1 0 1 1 1
 *	 b ->	1 1 1 1 1 0 0
 *	 C ->	0 1 1 1 0 0 1
 *   d ->	1 0 1 1 1 1 0
 *   E ->	1 1 1 1 0 0 1
 *   F ->	1 1 1 0 0 0 1
 *
 *      _A
 *	  F|_|B
 *	  E|_|C
 *      D
 */

#include <avr/io.h>
#include <avr/delay.h>

#define F_CPU 16000000UL

const uint8_t segment_look_up[] ={
		0b00111111,//0
		0b00000110,//1
		0b01011011,//2
		0b01001111,//3
		0b01100110,//4
		0b01101101,//5
		0b01111101,//6
		0b00000111,//7
		0b01111111,//8
		0b01101111,//9
		0b01110111,//A
		0b01111100,//b
		0b00111001,//C
		0b01011110,//d
		0b01111001,//E
		0b01110001 //F
};

int main()
{
	DDRD = 0b01111111;
	//Following will have same effect
	//DDRD |= (1<<DDD6)|(1<<DDD5)|(1<<DDD4)|(1<<DDD3)|(1<<DDD2)|(1<<DDD1)|(1<<DDD0);
	//DDRD |= _BV(DDD6)|_BV(DDD5)|_BV(DDD4)|_BV(DDD3)|_BV(DDD2)|_BV(DDD1)|_BV(DDD0);
	PORTD = 0x00;
	uint8_t i;
	while(1)
	{
		for(i=0;i<15;i++)
		{
			PORTD= segment_look_up[i];
			_delay_ms(2000);
		}

	}

}
