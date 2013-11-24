#include <avr/io.h>
#include <util/delay.h>	

/**
	LED Blink operation
*/
int main(void)
{
	DDRB |=  0 << PINB0;		// creates the mask ..decimal 1= 00000001 shifted by PINB0 i.e. 0
	
	/*
		Note 1 << PINB0 is a way of creating a mask for port pins.. 
		we could say 1 << PINB5 to create a mask for PB5 == 0b00100000
	*/
/*	while(1)
	{
		PORTB ^= 1 << PINB0; // xor operation flips the bits
		_delay_ms(100);
//		PORTB |= 1 << PINB0 ;		// push PBO to high +5V
//		_delay_ms(1000);
//		PORTB &= ~(1 << PINB0);		// push PBO to low 0V
//		_delay_ms(1000);
	}
*/


}