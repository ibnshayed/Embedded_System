/*
 * Main.c
 *
 *  Created on: Aug 2, 2019
 *      Author: ibnshayed
 */


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 16000000UL
#define F_OSC 16000000 //hz
// PE0(atmega128) PD0(328P) or RXD0 -> Bluetooth HC-05 TX
//PE1(atmega128) PD1(328P) or TXD0-> Bluetooth HC-05 RX

#define LEDs_DDR DDRC
#define LEDs_PORT PORTC
#define LED0 PC0
#define LED1 PC1
#define LED2 PC2
#define LED3 PC3
#define LED4 PC4
#define LED5 PC5

///USART
#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR F_OSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067*/
////////////////USART Start///////////////////////////////////////
void USART_init(unsigned int ubrr) {

	UCSR0C = (0 << USBS0) | (3 << UCSZ00); /// Step 1. Set UCSR0C in Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UCSR0A = 0b00000000; /// Step 2. Set UCSR0A in Normal speed, disable multi-proc

	UBRR0H = (unsigned char) (ubrr >> 8); /// Step 3. Load ubrr into UBRR0H and UBRR0L
	UBRR0L = (unsigned char) ubrr;

	UCSR0B = 0b00011000; /// Step 4. Enable Tx Rx and disable interrupt in UCSR0B
}
int USART_send(char c, FILE *stream) {

	while (!( UCSR0A & (1 << UDRE0))) /// Step 1.  Wait until UDRE0 flag is high. Busy Waitinig
	{
		;
	}

	UDR0 = c; /// Step 2. Write char to UDR0 for transmission
}
int USART_receive( FILE *stream) {

	while (!(UCSR0A & (1 << RXC0)))
		/// Step 1. Wait for Receive Complete Flag is high. Busy waiting
		;

	return (UDR0); /// Step 2. Get and return received data from buffer
}
//////////////USART END
void init_LEDs() {
	LEDs_DDR |= (1 << LED0) | (1 << LED1) | (1 << LED2) | (1 << LED3)
			| (1 << LED4) | (1 << LED5);
	LEDs_PORT &= ~(1 << LED0) | ~(1 << LED1) | ~(1 << LED2) | ~(1 << LED3)
			| ~(1 << LED4) | ~(1 << LED5);
}
int main() {

	unsigned char command;
	USART_init(MYUBRR);
	init_LEDs();
	// Initialise the standard IO handlers
	stdout = fdevopen(USART_send, NULL);
	stdin = fdevopen(NULL, USART_receive);
	printf("initialized\r\n");
	while (1) {
		scanf("%c", &command);
		switch (command) {
		case '0':
			LEDs_PORT ^= (1 << LED0);
			printf("LED0 is %d\r\n",(LEDs_PORT&(1<<LED0))>>LED0);
			break;
		case '1':
			LEDs_PORT ^= (1 << LED1);
			printf("LED1 is %d\r\n",(LEDs_PORT&(1<<LED1))>>LED1);
			break;
		case '2':
			LEDs_PORT ^= (1 << LED2);
			printf("LED2 is %d\r\n",(LEDs_PORT&(1<<LED2))>>LED2);
			break;
		case '3':
			LEDs_PORT ^= (1 << LED3);
			printf("LED3 is %d\r\n",(LEDs_PORT&(1<<LED3))>>LED3);
			break;
		case '4':
			LEDs_PORT ^= (1 << LED4);
			printf("LED4 is %d\r\n",(LEDs_PORT&(1<<LED4))>>LED4);
			break;
		case '5':
			LEDs_PORT ^= (1 << LED5);
			printf("LED5 is %d\r\n",(LEDs_PORT&(1<<LED5))>>LED5);
			break;
		default:
			printf("received %c\r\n", command);
			break;

		}



		_delay_ms(100);
	}
}
