/*
 * Main.c
 *
 *  Created on: Aug 22, 2019
 *      Author: ibnshayed
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define F_CPU 16000000UL

#define FOSC 16000000 /**< Clock speed for UBRR calculation. refer page 179 of 328p datasheet. */
#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR FOSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067*/

#define numSlots 20
#define DELAY 100

int result;
volatile int count = 0;
volatile int revolution = 0;
volatile uint8_t flag = 0;
/////////////////////USART Start////////////////
/**
 * @brief Initialize USART for 8 bit data transmit no parity and 1 stop bit.
 *
 *@details This is a code snippet from datasheet page 182
 *
 * @param ubrr The UBRR value calculated in macro MYUBRR
 * @see MYUBRR
 */
void USART_init(unsigned int ubrr) {

	UCSR0C = (0 << USBS0) | (3 << UCSZ00); /// Step 1. Set UCSR0C in Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UCSR0A = 0b00000000; /// Step 2. Set UCSR0A in Normal speed, disable multi-proc

	UBRR0H = (unsigned char) (ubrr >> 8); /// Step 3. Load ubrr into UBRR0H and UBRR0L
	UBRR0L = (unsigned char) ubrr;

	UCSR0B = 0b00011000; /// Step 4. Enable Tx Rx and disable interrupt in UCSR0B
}

/**
 * @brief Send 8bit data.
 *
 *@details This is a code snippet from datasheet page 184
 *
 * @param data The 8 bit data to be sent
 */

int USART_send(char c, FILE *stream) {

	while (!(UCSR0A & (1 << UDRE0))) /// Step 1.  Wait until UDRE0 flag is high. Busy Waitinig
	{
		;
	}

	UDR0 = c; /// Step 2. Write char to UDR0 for transmission
}

/**
 * @brief Receive 8bit sata.
 *
 *@details This is a code snippet from datasheet page 187
 *
 * @return Returns received data from UDR0
 */
int USART_receive(FILE *stream) {

	while (!(UCSR0A & (1 << RXC0)))
		/// Step 1. Wait for Receive Complete Flag is high. Busy waiting
		;

	return UDR0; /// Step 2. Get and return received data from buffer
}
////////////////USART END////////////////
ISR(PCINT0_vect) {
	if (count < 20) {
		count++;
	} else {
		revolution++;
		count = 0;
		flag = 1;
	}

}

void init_pcint0() {
	/*DDRD &= ~(1 << DDD2); /// Set int0 as input
	 PORTD |= (1 << PD2); /// pullup
	 EICRA |= (1 << ISC01); /// EICRA – External Interrupt Control Register A ; ISC01, ISC00 = 1,1 a Rising edge triggers interrupt
	 EICRA |= (1 << ISC00);
	 EIMSK |= (1 << INT0); /// Enable INT0*/
	DDRB &= ~(1 << PB2);
	PORTB |= (1 << PB2);

	PCICR |= (1 << PCIE0);
	PCIFR |= (1 << PCIF0);
	PCMSK0 |= (1 << PCINT0);
}

void init_ADC() {
	/// ADMUX section 23.9.1 page 262
	///BIT 7 and BIT 6  AVCC with external capacitor at AREF pin REFS0 =0 and REFS1= 1
	/// BIT 5  ADC Left Adjust Result ADLAR = 0
	/// BIT 3:0 MUX3:0 0b0000 for channel 0
	ADMUX = 0b01000000;
	//same as previous line
	//	ADMUX = (_BV(REFS0))| (ADMUX & ~_BV(REFS1))|(_BV(ADLAR))|(ADMUX & ~_BV(MUX3))|(ADMUX & ~_BV(MUX2))|(ADMUX & ~_BV(MUX1))|(ADMUX & ~_BV(MUX0));

	///DIDR0  Digital Input Disable Register 0 section Section 23.9.4 page 265 - 266
	/// Disable digital input buffer of ADC0 to save power consumption
	//DIDR0 = 0b00000001;

	/// ADSCRA ADC Control and Status Register A Section 23.9.2 page 263 -264
	///Bit 7  ADEN: ADC Enable =1 enable ADC
	///Bit 6  ADSC: ADC Start Conversion =0 do not start conversion
	///Bit 5  ADATE: ADC Auto Trigger Enable = 0 Disable trigger
	///Bit 4  ADIF: ADC Interrupt Flag = 0
	///Bit 3  ADIE: ADC Interrupt Enable = 0 Disable ADC interrupt
	///Bits 2:0  ADPS2:0: ADC Prescaler Select Bits 010 division factor = 4
	ADCSRA = 0b10000111;

}

uint16_t read_ADC(uint8_t ch) {
	// select the corresponding channel 0~7
	// ANDing with ’7′ will always keep the value
	// of ‘ch’ between 0 and 7
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8) | ch; // clears the bottom 3 bits before ORing

	// start single convertion
	// write ’1′ to ADSC
	ADCSRA |= (1 << ADSC);

	// wait for conversion to complete
	// ADSC becomes ’0′ again
	// till then, run loop continuously
	while (ADCSRA & (1 << ADSC))
		;

	return (ADC);
}

uint8_t graycode_table[64] = { 0b00000000, 0b00000001, 0b00000011, 0b00000010,
		0b00000110, 0b00000111, 0b00000101, 0b00000100, 0b00001100, 0b00001101,
		0b00001111, 0b00001110, 0b00001010, 0b00001011, 0b00001001, 0b00001000,
		0b00011000, 0b00011001, 0b00011011, 0b00011010, 0b00011110, 0b00011111,
		0b00011101, 0b00011100, 0b00010100, 0b00010101, 0b00010111, 0b00010110,
		0b00010010, 0b00010011, 0b00010001, 0b00010000, 0b00110000, 0b00110001,
		0b00110011, 0b00110010, 0b00110110, 0b00110111, 0b00110101, 0b00110100,
		0b00111100, 0b00111101, 0b00111111, 0b00111110, 0b00111010, 0b00111011,
		0b00111001, 0b00111000, 0b00101000, 0b00101001, 0b00101011, 0b00101010,
		0b00101110, 0b00101111, 0b00101101, 0b00101100, 0b00100100, 0b00100101,
		0b00100111, 0b00100110, 0b00100010, 0b00100011, 0b00100001, 0b00100000

};

int main() {

	init_ADC();
	USART_init(MYUBRR);
	stdout = fdevopen(USART_send, NULL);
	stdin = fdevopen(NULL, USART_receive);

	init_pcint0();
	sei();
	/// Enable global interrupt
	//DDRD |= (1 << DDD5) | (1 << DDD6);

	//Defining angle range;
	double minAngle[64];
	double maxAngle[64];
	double anglePerDivision = 5.625;

	DDRB = 0x3F;
	PORTB |= (1 << PD5);
	PORTB &= ~(1 << PD6);

	while (1) {
		uint8_t i = 0;
		uint8_t j = 0;
		result = read_ADC(0b01000000);
		//printf("{\"adc0%d\":%d}\n", bit_is_set(ADMUX, 0), result);
		_delay_ms(100);

		for (i = 0; i < 64; i++) {
			PORTB = graycode_table[i];

			if (i == 0) {
				minAngle[i] = 0;
				maxAngle[i] += anglePerDivision;
			}
			if(i >0 && i<64) {
				minAngle[i] = maxAngle[i - 1];
				maxAngle[i] += anglePerDivision;

			}
			if (result == graycode_table[i]) {
				printf("Range is %.3lf degree to %.3lf degree.", minAngle[i],
						maxAngle[i]);
				_delay_ms(DELAY);
				break;
			}

		}




	}
}

