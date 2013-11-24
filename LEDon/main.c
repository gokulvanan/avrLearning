#include <avr/io.h>

/*
	Program to keep the LED ON in PB0 register
*/
int main(void)
{
	DDRB = 0b	0001;		// Set PB0 as output register
	
	
	while(1)
	{
		PORTB = 0b00000001;		// push PBO to high +5V
	}



}