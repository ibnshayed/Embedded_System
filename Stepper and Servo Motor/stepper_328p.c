/*
 * stepper_328p.c
 *
 *  Created on: Dec 8, 2016
 *      Author: rezwan
 */


/*
 * stepper_328p.c
 *
 *  Created on: Dec 7, 2016
 *      Author: rezwan
 */

#include <avr/io.h>
#include <util/delay.h>

//#define stdio
//#define FSM

#ifdef stdio
#include <stdio.h>

///USART
#define F_OSC 16000000UL

#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR F_OSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming 16MHz clock UBRR0 becomes 0x0067*/
#endif


#define Stepper_PORT PORTC
#define Stepper_DDR DDRC

#define A PC3
#define A_Prime PC2
#define B PC1
#define B_Prime PC0

#define L298_EN PC4

#ifdef FSM
#define Num_steps_Wave 4
#define Num_steps_Full 4
#define Num_steps_Half 8

#define mode_Wave 0
#define mode_Full 1
#define mode_Half 2

#define step_change_Full_Wave 2
#define step_change_Half 1

#define Clockwise 0
#define CounterClockwise 1

#define min_delay 50 //ms

uint8_t mode;
int step_change;
uint8_t direction;
#endif


const uint8_t wave_drive_FSM[4]=
{
		/*
			A	A'	B	B'
			1	0	0	0
			0	0	1	0
			0	1	0	0
			0	0	0	1

		  */
		0b1000,
		0b0010,
		0b0100,
		0b0001
};

const uint8_t Full_step_FSM[4]=
{
		/*
			A	A'	B	B'
			1	0	0	0
			1	0	1	0
			0	1	1	0
			0	1	0	1

		  */
		0b1000,
		0b1010,
		0b0110,
		0b0101
};

const uint8_t Half_step_FSM[8]=
{
		/*
			A	A'	B	B'
			1	0	0	0
			1	0	1	0
			0	0	1	0
			0	1	1	0
			0	1	0	0
			0	1	0	1
			0	0	0	1
			1	0	0	1

		  */
		0b1000,
		0b1010,
		0b0010,
		0b0110,
		0b0100,
		0b0101,
		0b0001,
		0b1001,
};
#ifdef FSM
void init_stepper_ports();
void initialize_stepper_param(uint8_t mode, uint8_t direction);
void stepper_FSM(long steps);
void set_mode(uint8_t mode);
void set_direction(uint8_t direction);
uint8_t get_index(long step_count);
#endif
#ifdef stdio
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
#endif
void init_stepper_ports()
{
	Stepper_DDR |= (1<<A)|(1<<A_Prime)|(1<<B)|(1<<B_Prime)|(1<<L298_EN);
	Stepper_PORT &= ~(1<<L298_EN);// Disable L298
}
#ifdef FSM
void initialize_stepper_param(uint8_t new_mode, uint8_t new_direction)
{
	set_mode(new_mode);
	set_direction(new_direction);
}
uint8_t get_index(long int step_count)
{
	uint8_t idx = 0;
	uint8_t temp_idx=0;
	switch(mode)
	{
		case mode_Half:
		case mode_Wave:
			if(step_count%8 < 0)
			{
				idx = (step_count%8)+8;
			}
			else
				idx = step_count%8;
			break;
		case mode_Full:

			if(step_count%8 < 0)
			{
				temp_idx = (step_count%8)+8;
			}
			else
				temp_idx = step_count%8;

			if(temp_idx)
				idx = (temp_idx)-1;
			break;
	}
	printf("index %d\n",idx);
	return idx;
}
void stepper_FSM(long steps)
{
	static long int step_counter=0;
	long i =0;
	uint8_t bit_mask=0b1111;
	for(i=0;i<steps;i++)
	{
		Stepper_PORT = (Stepper_PORT & ~(bit_mask))|(Half_step_FSM[get_index(step_counter)]);
		if(direction== Clockwise){
			step_counter +=(long int) step_change;
		}
		else{
			step_counter-=(long int) step_change;
		}
		_delay_ms(min_delay);
	}
}
void set_mode(uint8_t new_mode)
{
	switch(new_mode)
		{
			case mode_Full:
				mode = new_mode;
				step_change = step_change_Full_Wave;
				break;
			case mode_Wave:
				mode = new_mode;
				step_change = step_change_Full_Wave;
				break;
			case mode_Half:
				mode = new_mode;
				step_change = step_change_Half;
				break;
			default:
				mode = mode_Full;
				step_change = step_change_Full_Wave;
				break;
		}
}

void set_direction(uint8_t new_direction)
{
	switch(new_direction)
		{
			case Clockwise:
				direction = new_direction;
				break;
			case CounterClockwise:
				direction = new_direction;
				break;
			default:
				direction = new_direction;
				break;
		}
}
#endif
int main()
{
#ifdef stdio
		USART_init(MYUBRR);
	    // Initialise the standard IO handlers
	    stdout = fdevopen(USART_send, NULL);
	    stdin = fdevopen(NULL, USART_receive);
#endif
	init_stepper_ports();
#ifdef FSM
	initialize_stepper_param(mode_Full,Clockwise);
#endif
#ifndef FSM
	uint8_t bit_mask=0b1111;
#endif
	Stepper_PORT |= (1<<L298_EN);
	while(1)
	{
	#ifdef FSM
		stepper_FSM(10);
		_delay_ms(300);
	#endif
#ifndef FSM
		for(int i=0;i<8;i++)
		{

			Stepper_PORT = (Stepper_PORT & ~(bit_mask))|(Half_step_FSM[i]);

			_delay_ms(50);
		}
#endif
	}
}
