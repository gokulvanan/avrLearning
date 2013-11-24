#include<avr/io.h>


/**
	MCU intercommunication - Polling approach
	Reciever code
*/

int main(void)
{
	// Initialize code for  LED BUTTON, 
	DDRB |= 1<< PINB0;     // output pins
	PORTB &= ~(1 <<PINB0); // PB0 is off
	
	
	//And USART Spec (parity, databit length and stopBits)
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
		
		// check if rx buffer in ready to get daya
		// RXC butter is full
			while( !(UCSRA &( 1 << RXC)));
			unsigned char rxdata = UDR;
			if(rxdata == 0b11110000)
			{
				//Toggle LED
				PORTB  ^= 1 << PINB0;
			}
		// Get Data
		// Check if data is as expected
		// if so toggle the LED
	}
	
}