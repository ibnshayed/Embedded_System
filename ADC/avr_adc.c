/*
 * avr_adc.c
 *
 *  Created on: Jun 15, 2015
 *      Author: rezwan
 */
#include <avr/io.h>
#include <util/delay.h>


#define F_CPU 16000000UL

uint8_t result;

void init_ADC()
{
	/// ADMUX section 23.9.1 page 262
	///BIT 7 and BIT 6 – AVCC with external capacitor at AREF pin REFS0 =0 and REFS1= 1
	/// BIT 5 – ADC Left Adjust Result ADLAR = 1
    /// BIT 3:0 –MUX3:0 0b0000 for channel 0
	ADMUX = 0b01100000;
	//same as previous line
	//	ADMUX = (_BV(REFS0))| (ADMUX & ~_BV(REFS1))|(_BV(ADLAR))|(ADMUX & ~_BV(MUX3))|(ADMUX & ~_BV(MUX2))|(ADMUX & ~_BV(MUX1))|(ADMUX & ~_BV(MUX0));

	///DIDR0 – Digital Input Disable Register 0 section Section 23.9.4 page 265 - 266
	/// Disable digital input buffer of ADC0 to save power consumption
	DIDR0 = 0b00000001;

	/// ADSCRA ADC Control and Status Register A Section 23.9.2 page 263 -264
	///Bit 7 – ADEN: ADC Enable =1 enable ADC
	///Bit 6 – ADSC: ADC Start Conversion =0 do not start conversion
	///Bit 5 – ADATE: ADC Auto Trigger Enable = 0 Disable trigger
	///Bit 4 – ADIF: ADC Interrupt Flag = 0
	///Bit 3 – ADIE: ADC Interrupt Enable = 0 Disable ADC interrupt
	///Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits 010 division factor = 4
	ADCSRA = 0b10000010;

}
int main()
{
	DDRD = 0xFF;
	PORTD = 0x00;
	init_ADC();
	while(1)
	{
		ADCSRA |= (1<<ADSC);
		while (bit_is_set(ADCSRA,ADSC))
		{
			;
		}
		result = ADCH;
		PORTD = result;


	}
}
