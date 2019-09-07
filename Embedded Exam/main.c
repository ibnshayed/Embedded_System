/*
 * ADC_Example.c
 *
 * Created: 6/5/2017 12:58:46 PM
 * Author : chuck
 */ 

#include <avr/io.h>
unsigned int Ctemp;
unsigned int Ftemp;

int main(void)
{
    /* Replace with your application code */
 	ADMUX = (1<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (1<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);
	ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADEN);
	
	ADCSRA |= (1<<ADSC);
	
	while ((ADCSRA & (1<<ADSC)) !=0);
	
    while (1) 
    {
    ADCSRA |= (1<<ADSC);
	while ((ADCSRA & (1<<ADSC)) !=0);
	
	Ctemp = (ADC - 247)/1.22;
	Ftemp = (Ctemp * 1.8) + 32;
	}
	return -1;
}

