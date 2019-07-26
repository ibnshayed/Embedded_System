/*
 * running_led.c
 *
 *  Created on: Jul 6, 2017
 *      Author: rezwan
 */

#include <avr/io.h>
#include <util/delay.h>
#define Part1
//#define Part2
//#define Part2A

int main()
{

	DDRD = 0xFF;
	PORTD = 0x00;
#ifdef Part2A
	uint8_t pattern[]={
			0b00011000,
			0b00100100,
			0b01000010,
			0b10000001,
			0b01000010,
			0b00100100,
			0b00011000
	};
//	uint8_t pattern[]=
//	{
//			0b00000001,
//			0b00000010,
//			0b00000100,
//			0b00001000,
//			0b00010000,
//			0b00100000,
//			0b01000000,
//			0b10000000,
//			0b01000000,
//			0b00100000,
//			0b00010000,
//			0b00001000,
//			0b00000010,
//			0b00000001,
//
//	};
	while(1){
		for(uint8_t i =0; i<7;i++){
			PORTD = pattern[i];
			_delay_ms(300);
		}
	}
#endif
///Part 2
#ifdef Part2
	uint8_t Left, Right, i;
	Left= 0b0000001;
	Right=0b0001000;
	while(1){
		for(i=0;i<4;i++)
		{
			PORTD = (Left<<4)|(Right);
			Left = Left<<i;
			Right = Right>>i;
			_delay_ms(300);
		}
		Left= 0b0001000;
		Right=0b0000001;
		for(i=0;i<4;i++){
			PORTD = (Left<<4)|(Right);
			Left = Left>>i;
			Right = Right<<i;
			_delay_ms(300);
		}

		Left= 0b0000001;
		Right=0b0001000;

	}
#endif
// Part 1
#ifdef Part1
	uint8_t i,j,k,l, RightToLeft, LeftToRight;
	j = 1;
	k = 6;
	RightToLeft = 0x01;
	LeftToRight = 0x80;
	while(1)
	{
		for(l=0;l<8;l++)
		{
			for(i=0;i<8;i++){

				PORTD = RightToLeft<<i;
				_delay_ms(100);
			}
			RightToLeft |= (1<<j);
			j++;

			for(i=0;i<8;i++){
				PORTD = LeftToRight >>i;
				_delay_ms(100);
			}
			LeftToRight |= (1<<k);
			k--;
		}
			j = 1;
			k = 6;
			RightToLeft = 0x01;
			LeftToRight = 0x80;

	}
#endif
}
