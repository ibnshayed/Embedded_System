/*
 * For more timer tutorial go to
 * http://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-timers?page=all
 */

/**
 * @file timer1.c
 * @author rezwan
 * @date 09.08.2015
 *
 * @brief AVR ATMEGA328P Timer1 example example for CSE3023.
 *
 * 	A simple program measures elapsed time. Demonstrates Timer1 calculation, and ISR. Also demonstrates printf() functionality
 *  Eclipse may cause problem in macro resolution = 'Symbol abc could not be resolved'.
 *  If someone encounters this problem following steps should resolve the matter.
 *  In the project explorer right click on the project then go to 'index' and left click on Rebuild'
 *
 * For more timer tutorial go to http://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-timers?page=all
*/
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h> // to print uint32_t
#define F_CPU 16000000UL /**< Clock speed for delay functions. */


#define FOSC 16000000 /**< Clock speed for UBRR calculation. refer page 179 of 328p datasheet. */
#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR FOSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067*/

volatile uint32_t n; /**< n to count elapsed time */

/**
 * @brief Initialize USART for 8 bit data transmit no parity and 1 stop bit.
 *
 *@details This is a code snippet from datasheet page 182
 *
 * @param ubrr The UBRR value calculated in macro MYUBRR
 * @see MYUBRR
*/
void USART_init(unsigned int ubrr)
{

	UCSR0C = (0<<USBS0)|(3<<UCSZ00); /// Step 1. Set UCSR0C in Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UCSR0A = 0b00000000;/// Step 2. Set UCSR0A in Normal speed, disable multi-proc

	UBRR0H = (unsigned char)(ubrr>>8);/// Step 3. Load ubrr into UBRR0H and UBRR0L
	UBRR0L = (unsigned char)ubrr;


	UCSR0B = 0b00011000;/// Step 4. Enable Tx Rx and disable interrupt in UCSR0B
}

/**
 * @brief Send 8bit data.
 *
 *@details This is a code snippet from datasheet page 184
 *
 * @param c The 8 bit data to be sent
 * @param FILE *stream to receive
*/

int USART_send(char c, FILE *stream)
{


	while ( !( UCSR0A & (1<<UDRE0)) )/// Step 1.  Wait until UDRE0 flag is high. Busy Waitinig
	{;}

	UDR0 = c; /// Step 2. Write char to UDR0 for transmission

}

/**
 * @brief Receive 8bit data.
 *
 *@details This is a code snippet from datasheet page 187
 *
 * @return Returns received data from UDR0
*/
int USART_receive(FILE *stream)
{

while ( !(UCSR0A & (1<<RXC0)) )/// Step 1. Wait for Receive Complete Flag is high. Busy waiting
;

return UDR0;/// Step 2. Get and return received data from buffer
}

/**
 * @brief ISR for  TIMER1 overflow. Increase value of n.
*/
ISR(TIMER1_OVF_vect)
{

	n++;
}
void timer1_init()
{

	TCCR1A = 0b00000000; ///Step 1.  normal mode
	TCCR1B = 0b00000011; ///Step 2. 1:64 prescaler, internal clock
	TIMSK1 = 0b00000001; ///Step 3. enable Timer 1 overflow interrupt
}

/**
 * @brief Program entry point.
 *
 *@detail
 *Initialize the timer1 register.
 *Initialize usart communication.
 *Initialize the standard IO handlers for printf.
 *Initialize the standard IO handlers for scanf.
 * Reset counter.
 * Reset Timer1.
 * Enable global interrupt.
 * run a random loop.
 * print  the result.
 *
*/
int main()
{

	USART_init(MYUBRR);
	timer1_init();
	int i,j;
	uint32_t elapse_time;
	stdout = fdevopen(USART_send, NULL); // Initialize the standard IO handlers for printf
	stdin = fdevopen(NULL, USART_receive);// Initialize the standard IO handlers for scanf
while(1)
	{

		n = 0; // reset n
		TCNT1 = 0; // reset Timer 1
		sei();
		for (i =0;i<100;i++)
			for(j=0;j<1000;j++)
		{

		}

		elapse_time = n * 262144 + (uint32_t) (TCNT1*4) ; /// Target Period = ((2 ^ 16) * (Prescale / 16000000) = ((2 ^ 16) * (64 / 16000000) = 0.262144 = 262144 uS (approx.) TCNT1 1 is 4uS
		cli();
		printf("Elapsed time = %"PRId32" uS \r",elapse_time);


	}
}


