/*
 * Main.c
 *
 *  Created on: Aug 4, 2019
 *      Author: ibnshayed
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 16000000UL

int main() {
    DDRB = 0b00001111;
    PORTB = 0x00;
    int i = 1;
    while (1) {

        if(i == 256)
            i = 1;

        PORTB = 0b00001000;
        _delay_ms(10);
        PORTB = 0b00000100;
        _delay_ms(10);

        PORTB = 0b00000010;
        _delay_ms(10);
        PORTB = 0b00000001;
        _delay_ms(10);

        i++;
        if(i == 128)
        _delay_ms(3000);


    }
}

