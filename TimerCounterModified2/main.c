#include<avr/io.h>

int main (void)
{
	// initialize the ports for the LED
	DDRB |= (1 << PINB0) | (1 << PINB2); // mark B0 as output
	PORTB &= ~(1 << PINB0 | 1 << PINB1) ; // keep B0 low at start
	TCCR1B  |= (1 << CS10) | (1 << CS11); // count as per MCU clock/64 = 1000000/64 = 15625 
	uint8_t rcount = 0;
	while(1)
	{
		// count and turn the LED on and off
		// TCNT1 counts 15625 times every second
		// i.e. from 0 to 15624
		// therefore for 1/7 of second TCNT1 would count 15624/7 = 2232
		if(TCNT1 > 2232)// check count in counter register
		{ 
			TCNT1 = 0; // reset the counter
			PORTB ^= (1 << PINB0);  // B0 tollges ever 1/7 second
			
			if(rcount++ > 6) // B1 toggles every second 
			{
				rcount = 0;
				PORTB ^= (1 << PINB2);
			}
			
		}
	}
}