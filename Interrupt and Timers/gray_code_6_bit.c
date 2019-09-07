/*
 * gray_code_6_bit.c
 *
 *  Created on: Dec 9, 2018
 *      Author: rezwan
 */

#include <avr/io.h>
#include <util/delay.h>
#define DELAY 100

uint8_t graycode_table[64]={
		0b00000000, 0b00000001, 0b00000011, 0b00000010,
		0b00000110, 0b00000111, 0b00000101, 0b00000100,
		0b00001100, 0b00001101, 0b00001111, 0b00001110,
		0b00001010, 0b00001011, 0b00001001, 0b00001000,
		0b00011000, 0b00011001, 0b00011011, 0b00011010,
		0b00011110, 0b00011111, 0b00011101, 0b00011100,
		0b00010100, 0b00010101, 0b00010111, 0b00010110,
		0b00010010, 0b00010011, 0b00010001, 0b00010000,
		0b00110000, 0b00110001, 0b00110011, 0b00110010,
		0b00110110, 0b00110111, 0b00110101, 0b00110100,
		0b00111100, 0b00111101, 0b00111111, 0b00111110,
		0b00111010, 0b00111011, 0b00111001, 0b00111000,
		0b00101000, 0b00101001, 0b00101011, 0b00101010,
		0b00101110, 0b00101111, 0b00101101, 0b00101100,
		0b00100100, 0b00100101, 0b00100111, 0b00100110,
		0b00100010, 0b00100011, 0b00100001, 0b00100000

};
int main(){
	uint8_t i =0;
	DDRD = 0x3F;
	for(i=0;i<64;i++){
		PORTD = graycode_table[i];
		_delay_ms(DELAY);
	}

}