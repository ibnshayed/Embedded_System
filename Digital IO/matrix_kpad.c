/*
 * matrix_kpad.c
 *
 *  Created on: Oct 28, 2018
 *      Author: rezwan
 */
#include <avr/io.h>
#include <util/delay.h>

#define matrixDDR DDRD
#define matrixPORT PORTD
#define matrixPIN PIND

uint8_t matriKpad[4][3]={
		{1,2,3},
		{4,5,6},
		{7,8,9},
		{'*',0,'#'}
};
uint8_t getMatrixKpad(){
	uint8_t row, column;
	matrixPORT |= 0b01111000; // rows are high
	for(column = 0;column<3; column++){
		matrixDDR = 0x00;
		matrixDDR |= (1<<column);
		for(row =3;row<7;row++){
			if(bit_is_clear(matrixPIN,row)){
				return matriKpad[row-3][column];
			}
		}

	}
	return 0xFF;
}
int main(){
	DDRC = 0b00111111;
	PORTC = 0x00;
while(1){
	uint8_t k= getMatrixKpad();
	if(k!=0xFF)
	PORTC = k;
	//_delay_ms(100);
}
}
