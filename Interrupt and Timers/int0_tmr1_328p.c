
/**
 * @file int0_tmr1_328p.c
 * @author rezwan
 * @date 09.08.2015
 *
 * @brief AVR ATMEGA328P Timer1 example example for CSE3023.
 *
 *  A simple program measures elapsed time between two interrupts. We are using wheel disc encoder to generate interrupt. This encoder outputs low when there is no obstacle and high there is one. That's why the Int0 interrupts at rising edge.
 *  Demonstrates Timer1 calculation, and ISR. Also demonstrates printf() functionality.
 *  Eclipse may cause problem in macro resolution = 'Symbol abc could not be resolved'.
 *  If someone encounters this problem following steps should resolve the matter.
 *  In the project explorer right click on the project then go to 'index' and left click on Rebuild'
 *
 * For more timer tutorial go to http://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-timers?page=all
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <inttypes.h> // to print uint32_t

#define SLOTS_PER_REV 20 /**< Total slots in a encoder disc */
#define FOSC 16000000 /**< Clock speed for UBRR calculation. refer page 179 of 328p datasheet. */
#define BAUD 57600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR FOSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet.*/

volatile uint32_t revolution_count;  /**< Counter for revolution */
volatile int slot_count; /**< Counter for slots */
volatile uint32_t n; /**< n to count number of times TCNT1 overflowed */
volatile uint32_t elapse_time=0;/**< Stores cumulative revolution completion time */
volatile uint8_t flag = 0, print_flag=0;
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


	UCSR0B = 0b00001000;/// Step 4. Enable Tx Rx and disable interrupt in UCSR0B
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
	return 0;
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
 * @brief Interrupt service routine for Timer1 Overflow vector.
 *
 *@details It increases the value of n by one to number of time TIMER1 overflowed between two INT0 interrupts
 *
*/
ISR(TIMER1_OVF_vect)
{

	n++;
}
// ISR(BADISR_vect)
// {
//	int i;
//	i++;
// }
void timer1_init()
{

	TCCR1A = 0b00000000; ///Step 1.  normal mode
	TCCR1B = 0b00000011; ///Step 2. 1:64 prescaler, internal clock
	TIMSK1 = 0b00000001; ///Step 3. enable Timer 1 overflow interrupt
}

/**
 * @brief Interrupt service routine for INT0 vector.
 *
 *@details INT0 interrupt
 *
*/
ISR(INT0_vect)
{
	if (flag ==0) /// Exceuted only once for very first external interrupt and initites timer timer counter 
	{
		TCNT1 =0;
		n = 0;
		flag =1; /// Make the flag 1 so that it never enters again 
	}
	if (slot_count < SLOTS_PER_REV) /// smaller than total slots
	{
		slot_count ++; /// increase counter
	}
	else /// Completed one revolution
	{
		revolution_count ++; /// increase revolution counter
		print_flag=1; /// tell main loop that it may print new value
		slot_count =0; /// reset to start count for next revolution
		elapse_time += n * 262144 + (uint32_t) (TCNT1*4); /// Caclulate the elapsed time  (Prescaler * 2^16)/(Fosc) = 64 * 2^16 / 16MHz = 262144 uS. TCNT1 counter updates after = Prescaler/Fosc = 64/16MHz = 4uS 
		TCNT1 =0; /// reset counter to calculate next revolution
		n = 0;
	}
}

int main()
{

	slot_count =0;
	revolution_count = 0;
	USART_init(MYUBRR); /// Initialize USART
	stdout =fdevopen(USART_send,NULL); /// setup printf()

	DDRD &= ~(1<<DDD2);/// Set int0 as input



	EICRA |= (1<<ISC01); /// EICRA – External Interrupt Control Register A ; ISC01, ISC00 = 1,1 a Rising edge triggers an  interrupt
	EICRA |= (1<<ISC00);
	EIMSK|= (1<<INT0);/// Enable INT0
	timer1_init(); /// Initiate Timer1

	sei();/// Enable global interrupt
	while(1)
	{

		if(print_flag==1) /// If print_flag is high print the values
		{
			print_flag =0; /// Make print flag 0 so that it will print only when next revolution is complete
//			cli();
			printf("Number of revolution is %"PRId32" time taken %"PRId32" uS \r\n", revolution_count,elapse_time);
//			sei();
		}
		//wait for interrupt and do nothing
	};
	printf("end\n\r");
}
