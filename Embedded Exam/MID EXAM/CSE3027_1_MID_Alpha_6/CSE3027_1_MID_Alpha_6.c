/*
 * Doxygen tutorail site: http://wiki.vmars.tuwien.ac.at/index.php/Doxygen_Primer
 * and here http://mcuoneclipse.com/2012/06/25/5-best-eclipse-plugins-1-eclox-with-doxygen-graphviz-and-mscgen/
 * to make pdf output go to latex directory and run make command
 */

/**
 * @file usart.c
 * @author rezwan
 * @date 05.06.2015
 *
 * @brief AVR ATMEGA328P USART communication example for CSE3023.
 *
 * A simple echo program that receives a character from computer and echos it back.
 *  Eclipse may cause problem in macro resolution = 'Symbol xxx could not be resolved'.
 *  If someone encounters this problem following steps should resolve the matter.
 *  In the project explorer right click on the project then go to 'index' and left click on Rebuild'
 */
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define F_CPU 16000000UL /**< Clock speed for delay functions. */

#define FOSC 16000000 /**< Clock speed for UBRR calculation. refer page 179 of 328p datasheet. */
#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR FOSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067*/
int result;
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

/**
 * @brief Program entry point.
 *
 *@details This is a code snippet from datasheet page 187.
 *Initialize the usart communication.
 *Then in the while loop first wait for the data and then echo it back.
 *
 */

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

uint16_t analogRead(uint8_t ch) {
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

void pinMode(uint8_t pin, uint8_t mode) {

	printf("\npin = %d\tmode = %d", pin, mode);
	if (pin >= 2 && pin <= 7 && mode == 1) {
		DDRD |= _BV(pin);
		printf("\tPIN %d is set as OUTPUT.\n", pin);
	} else if (pin >= 2 && pin <= 7 && mode == 0) {
		DDRD &= ~_BV(pin);
		printf("\tPIN %d is set as INPUT.\n", pin);

	} else if (pin >= 8 && pin <= 13 && mode == 1) {
		DDRB |= _BV(pin - 8);
		printf("\tPIN %d is set as OUTPUT.\n", pin);
	} else if (pin >= 8 && pin <= 13 && mode == 0) {
		DDRB &= ~_BV(pin - 8);
		printf("\tPIN %d is set as INPUT.\n", pin);
	}
}

void digitalRead(uint8_t pin) {

	if (pin >= 2 && pin <= 7) {
		if (bit_is_set(DDRD, pin))
			printf("\tPIN %d is set as OUTPUT.\n", pin);
		else
			printf("\tPIN %d is set as INPUT.\n", pin);
	}
	if (pin >= 8 && pin <= 13) {
		if (bit_is_set(DDRB, pin - 8))
			printf("\tPIN %d is set as OUTPUT.\n", pin);
		else
			printf("\tPIN %d is set as INPUT.\n", pin);
	}

}

void digitalWrite(uint8_t pin, uint8_t mode) {

	printf("\npin = %d\tmode = %d", pin, mode);
	if (pin >= 2 && pin <= 7 && mode == 1) {
		DDRD |= _BV(pin);
		printf("\tPIN %d is set as OUTPUT.\n", pin);
	} else if (pin >= 2 && pin <= 7 && mode == 0) {
		DDRD &= ~_BV(pin);
		printf("\tPIN %d is set as INPUT.\n", pin);

	} else if (pin >= 8 && pin <= 13 && mode == 1) {
		DDRB |= _BV(pin - 8);
		printf("\tPIN %d is set as OUTPUT.\n", pin);
	} else if (pin >= 8 && pin <= 13 && mode == 0) {
		DDRB &= ~_BV(pin - 8);
		printf("\tPIN %d is set as INPUT.\n", pin);
	}
}

int main() {

	init_ADC();
	USART_init(MYUBRR);
	stdout = fdevopen(USART_send, NULL);
	stdin = fdevopen(NULL, USART_receive);

	DDRD = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;

	PORTD = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;

	unsigned char select;
	unsigned char a;
	unsigned char b;
	unsigned char m;

	uint8_t pin;
	uint8_t mode;

	while (1) {

		printf(
				"\n\n**pinMode(),digitalWrite() and digitalRead() for pin 2-13 and analogueRead() 0-5.\n");
		printf("Mode 0 as INPUT and 1 as OUTPUT.\n\n");
		printf("1. PinMode.\n");
		printf("2. DigitalRead.\n");
		printf("3. DigitalWrite.\n");
		printf("4. AnalogRead.\n");
		printf("\n Please select a opeation:\t");
		scanf("%c", &select);
		printf("\n\n");
		switch (select) {
		case '1':
			printf("PinMode:\tPIN: ");
			scanf("%c %c", &a, &b);  // input 2 value like 02 or 12 as pin
			printf("\tMODE: ");
			scanf("%c", &m);
			// ASCII value of 0 is 48
			//Converting char to uint8_t data type [value - 48]
			if (a - 48 == 0) {
				pin = b - 48;
			} else {
				pin = 10 + (b - 48);
			}

			mode = m - 48;
			pinMode(pin, mode);
			break;
		case '2':
			printf("DigitalRead:\tPIN: ");
			scanf("%c %c", &a, &b);
			// ASCII value of 0 is 48
			//Converting char to uint8_t data type [value - 48]
			if (a - 48 == 0) {
				pin = b - 48;
			} else {
				pin = 10 + (b - 48);
			}
			digitalRead(pin);
			break;
		case '3':
			printf("DigitalWrite:\tPIN: ");
			scanf("%c %c", &a, &b);
			printf("\tMODE: ");
			scanf("%c", &m);
			// ASCII value of 0 is 48
			//Converting char to uint8_t data type [value - 48]
			if (a - 48 == 0) {
				pin = b - 48;
			} else {
				pin = 10 + (b - 48);
			}

			mode = m - 48;
			digitalWrite(pin, mode);
			break;
		case '4':

			printf("AnalogRead:\tPIN: ");
			scanf("%c", &a); //input only one value
			pin = a - 48;
			printf("pin = %d\t",pin);
			if (pin == 0) {
				result = analogRead(0b01000000);
				printf("{\"adc0\":%d}\n",result);
				_delay_ms(100);
			}
			if (pin == 1) {
				result = analogRead(0b01000001);
				printf("{\"adc1\":%d}\n",result);
				_delay_ms(100);
			}
			if (pin == 2) {
				result = analogRead(0b01000010);
				printf("{\"adc2\":%d}\n",result);
				_delay_ms(100);
			}
			if (pin == 3) {
				result = analogRead(0b01000011);
				printf("{\"adc3\":%d}\n", result);
				_delay_ms(100);
			}
			if (pin == 4) {
				result = analogRead(0b01000100);
				printf("{\"adc4\":%d}\n",result);
				_delay_ms(100);
			}
			if (pin == 5) {
				result = analogRead(0b01000101);
				printf("{\"adc5\":%d}\n",result);
				_delay_ms(100);
			}

			break;
		default:
			break;
		}

	}
}

