#include<avr/io.h>
#define noOfButtons 2
#include"ButtonPress.h"

/**
	MCU intercommunication - Polling approach
	Transmitter code
*/

void transmitData(void);

int main(void)
{
	// Initialize code for  LED BUTTON, 
	DDRB |= 1<< PINB0;     // output pins
	DDRB &= ~( 1<< PINB1 ); // input pins
	PORTB &= ~(1 <<PINB0); // PB0 is off
	PORTB |= 1<< PINB1; // input pins are pulled high
	
	//And USART Spec (parity, databit length and stopBits)
	//setting up baud rate
	int UBRR_value = 25; //2400 baud rate with 0.2% error
	UBRRH= (unsigned char)(UBRR_value >> 8);
	UBRRL= (unsigned char)UBRR_value;
	
	// enable rx and tx USART control register
	UCSRB = (1 << RXEN | 1<<TXEN);
	
	//data bits 8 bits
	UCSRC |= 3<< UCSZ0;
	//2 stop bits
	
	UCSRC |= 1<<USBS;
	
	while(1)
	{
		
		if(ButtonPressed(0,PINB,1,500))
		{
			// toggle  LED
			PORTB ^= 1<< PINB0;
			// send data
			transmitData();
		}
		else
		{
		
		}
		
	}
	
}

void transmitData(void)
{
	while( !(UCSRA & (1<< UDRE))); //is UDRE bit in UCSRA is 0 keep looping (polling method)
	UDR=0b11110000; //send data
}