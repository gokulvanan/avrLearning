#include<avr/io.h>

int main (void)
{
	// initialize the ports for the LED
	DDRB |= (1 << PINB0); // mark B0 as output
	PORTB &= ~(1 << PINB0); // keep B0 low at start
	TCCR1B  |= (1 << CS10); // count as per MCU clock
	int rcount = 0;
	while(1)
	{
		// count and turn the LED on and off
		if(TCNT1 > 10000)// check count in counter register
		{ 
			TCNT1 = 0; // reset the counter
			/* 
				note reason why we have nested if instead of increasin the threshold 
				in the above if from 10000 for 1000K is beacuse the limit of TNCT1 is 65536
				// i.e. 2^16 for the 16 bit counter.. incase of TCNT0 it would 2^8 
				// but internal clk of mcu is aprox 1MHz.. 10^6 hence to get it to timing 
				of onesec per toggle blink we have the inner if looping 100 timse over 10K 
				i.e. 100 * 10K = 10^6
			*/
			
			if(rcount++ > 100) 
			{
				rcount = 0;
				PORTB ^= (1 << PINB0);
			}
			
		}
	}
}