#include <avr/io.h>
#include <util/delay.h>

/*
	Timers and Counter
*/
int main(void)
{

	//INIT
	DDRB = 0b01111111;
	DDRD = 0b01111111;
	PORTB = 0b00000000;
	PORTD = 0b00000000;
	//Timer counter control register - set to presace 64
	TCCR1B  |= 1 << CS10 | 1 <<CS11;
	uint8_t repeatCount = 0;
	int led[2];
	while(1)
	{
		//1000000/64 = 15625 -- due to prescale
		// hence TCNT1 counts 15625 times every second
		// i.e. from 0 to 15624
		// therefore for 1/7 of second TCNT1 would count 15624/7 = 2232
		if(TCNT1 > 2232) // 2232 = 15624/7; 
		{
			TCNT1=0;
			PORTB |= 1 << led[0];
			if(++led[0] > 6)
			{
				led[0] =0;
				PORTD |= 1 << led[1];
				if(++led[1] > 6)
				{
					led[1]=0;
				}
			}
		}
	}
}
