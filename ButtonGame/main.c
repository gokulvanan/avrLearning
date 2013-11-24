#include<avr/io.h>
#include<util/delay.h>
/*
	Button game
*/

// Function prototypes.. to be declared before main so that main knows about their declaration before being refrenced
// alternatively full definition of functions could be added here, with main at the bottom

void processPressedButton(int button);
void processReleasedButton(int button);


// Global variables
int pressed_cf [2]; // array to hold val used in software debounce check for each port
int released_cf [2];// array to hold val used in software debounce check for each port
int pressed [2];    // array to hold val to prevent multiple calls when button is held in infinite while loop
int led [2];		// array to hold led index val. and also deciede who is winner by flashing leds and resetting.

int main(void)
{
	DDRB = 0b01111111; // portB all registers are output except for PINB7
	DDRD = 0b01111111; // portD all registers are output except for PIND7
	PORTB = 0b10000000; // keep PINB7 as high
	PORTD = 0b10000000; /// keep PIND7 as high
	
	while(1)
	{
		if(bit_is_clear(PINB,7)){
			processPressedButton(0);
		}else{
			processReleasedButton(0);
		}
		if(bit_is_clear(PIND,7)){
			processPressedButton(1);
		}else{
			processReleasedButton(1);
		}
	}
}

void processPressedButton(int button)
{
	if(pressed_cf[button]++ > 500) // software debounce threshold
	{
		if(pressed[button] == 0) // check if button is pressed
		{
			if(button == 0) PORTB |= 1 << led[button];
			else if (button == 1) PORTD |= 1 << led[button];
			if(++led[button] > 6) // highlight winner
			{
				for(int i=0; i<10; i++){
					// go on
					if(button == 0) PORTB = 0b11111111;
					else if (button == 1) PORTD = 0b11111111;
					_delay_ms(10);
					// go off
					if(button == 0) PORTB = 0b10000000;
					else if (button == 1) PORTD = 0b10000000;
					_delay_ms(10);
				}
				//reset code
				led[0]=0;
				led[1]=0;
				PORTB = 0b10000000;
				PORTD = 0b10000000;	
			}
			pressed[button] = 1;
		}
		pressed_cf[button]=0;
	}
}



void processReleasedButton(int button)
{
	if(released_cf[button]++ > 500)
	{
		pressed[button]=0;
		released_cf[button]=0;
	}
}

