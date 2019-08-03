#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define F_CPU 16000000UL

#define FOSC 16000000 /**< Clock speed for UBRR calculation. refer page 179 of 328p datasheet. */
#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR FOSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067*/

volatile int count = 0;
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

	while (!( UCSR0A & (1 << UDRE0))) /// Step 1.  Wait until UDRE0 flag is high. Busy Waitinig
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
ISR(INT0_vect) {
	count++;
	flag = 1;
}
void init_int0() {
	DDRD &= ~(1 << DDD2); /// Set int0 as input
	PORTD |= (1 << PD2); /// pullup
	EICRA |= (1 << ISC01); /// EICRA – External Interrupt Control Register A ; ISC01, ISC00 = 1,1 a Rising edge triggers interrupt
	EICRA |= (1 << ISC00);
	EIMSK |= (1 << INT0); /// Enable INT0
}
int main() {

	USART_init(MYUBRR);
	stdout = fdevopen(USART_send, NULL);
	stdin = fdevopen(NULL, USART_receive);

	init_int0();
	sei();
	/// Enable global interrupt
	DDRD |= (1 << DDD5) | (1 << DDD6);
	PORTD |= (1 << PD5);
	PORTD &= ~(1 << PD6);

	while (1) {

		if (flag == 1) {
			printf("count %d\r\n", count);
			flag = 0;
		}
	}
}

