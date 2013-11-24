#include<avr/io.h>
#define noOfButtons 2
#include"ButtonPress.h"

/**
	Button Library code
*/

int main(void)
{
	DDRB |= 1<< PINB0 | 1<< PINB2;     // output pins
	DDRB &= ~( 1<< PINB1 | 1<< PINB4); // input pins
	DDRD &= ~( 1<< PIND0); // input pins
	PORTB |= 1<< PINB1 | 1<< PINB4 ; // input pins are pulled high
	PORTD  |= 1<< PIND0 ; // input pins are pulled high
	while(1)
	{
		if(ButtonPressed(0,PIND,0,500))
		{
			//toggle pinb2
			PORTB ^= 1<< PINB2;
		}
		if(ButtonPressed(1,PINB,4,500))
		{
			//toggle pinb0
			PORTB ^= 1<< PINB0;
		}
		if(ButtonPressed(2,PINB,1,500))
		{
			//toggle pinb 0
			PORTB ^= 1<< PINB0;
		}
		
	}
	
}