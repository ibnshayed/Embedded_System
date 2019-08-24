/*
 * rgbMain.c
 *
 *  Created on: Dec 18, 2017
 *      Author: rezwan
 */
/*
 * fast_pwm.c
 *
 *  Created on: Aug 16, 2015
 *      Author: administrator
 */

/*
 * PWM_test.c
 *
 *  Created on: Aug 17, 2013
 *      Author: rezwan
 */
//#define F_CPU 20000000UL
//#include <avr/io2313.h>
#include<avr/io.h>
#include<util/delay.h>
#include <stdio.h>
//#include <avr/iom328p.h>
#define F_CPU 16000000UL

#define RedChnl OCR1A
#define GreenChnl OCR1B
#define BlueChnl OCR0A

#define FOSC 16000000 /**< Clock speed for UBRR calculation. refer page 179 of 328p datasheet. */
#define BAUD 9600 /**< Baud Rate in bps. refer page 179 of 328p datasheet. */
#define MYUBRR FOSC/16/BAUD-1 /**< UBRR = (F_CPU/(16*Baud))-1 for asynch USART page 179 328p datasheet. Baud rate 9600bps, assuming	16MHz clock UBRR0 becomes 0x0067*/

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
 * @param data The 8 bit data to be sent
 */

int USART_send(char c, FILE *stream)
{

	while ( !( UCSR0A & (1<<UDRE0)) )/// Step 1.  Wait until UDRE0 flag is high. Busy Waitinig
	{;}

	UDR0 = c; /// Step 2. Write char to UDR0 for transmission
}

/**
 * @brief Receive 8bit sata.
 *
 *@details This is a code snippet from datasheet page 187
 *
 * @return Returns received data from UDR0
 */
int USART_receive(FILE *stream )
{

	while ( !(UCSR0A & (1<<RXC0)) )/// Step 1. Wait for Receive Complete Flag is high. Busy waiting
		;

	return UDR0;/// Step 2. Get and return received data from buffer
}
void init_TMR0(){
	OCR0A =255;

	TCCR0A |= (1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
	TCCR0B |= (1<<CS00);
	DDRD |= (1<<PD6);
}
void init_TMR1(){
			OCR1B = 255;
			OCR1A = 255;
	        TCCR1B|=(1<<WGM12);
	        TCCR1A|=(1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(1<<WGM10);


	        //COM1A1:COM1A0 =10 COM1B1:COM1B0 =10 and for Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at TOP
	        //For more information 2313 datasheet table 44 pg 104
	        // PWM_Frequency= F_osc / (PreScaler*(1+TOP))= 16MHz / (1*(1023+1))=  15625 = 15.63 KHz
	        // Resolution= log(TOP+1)/log(2)= 10 bit

	        TCCR1B|=(0<<CS12)|(0<<CS11)|(1<<CS10);//CS12->10 = 001 is for 1:1 timer pre-scaler. Start timer
	        DDRB|=(1<<PB2)|(1<<PB1);//OC1A and OC1B as output

}
int main(void)
{
        init_TMR0();
        init_TMR1();
        USART_init(MYUBRR);
        stdout = fdevopen(USART_send, NULL);
        stdin = fdevopen(NULL, USART_receive);
        RedChnl = 255;
        GreenChnl= 255;
        BlueChnl = 255;
        while(1)
        {

        	printf("Red Green Blue\n ");
        	scanf("%d %d %d",&RedChnl, &GreenChnl, &BlueChnl);


        }
}


