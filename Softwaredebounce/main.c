#include <avr/io.h>
#include <util/delay.h>	

/*
	Button click with softare debounce
*/

int main(void)
{
	DDRB |=  1 << PINB0;		// set PINB0 output
	PORTB ^= 1 << PINB0; 		// xor toggling only PORTB0
	DDRB |=  1 << PINB2;		// set PINB2 output
	
	DDRB &=  ~(1 << PINB1);	// set PINB1 input
	PORTB |= 1 << PINB1; 		// pull PINB1 high
	
	int press = 0;
	int pressed_cf=0;
	int released_cf=0;
	while(1) // infinite loop
	{
		if(bit_is_clear(PINB,1))
		{
			
			if (pressed_cf++ > 500)
			{
				if (press == 0 ) 
				{
					PORTB ^= 1 << PINB0;
					PORTB ^= 1 << PINB2;
					press = 1;
				}
				pressed_cf = 0;
			}
		}
		else
		{
			if(released_cf++ > 500)
			{
				press=0;
				released_cf=0;
			}
		}
	}



}