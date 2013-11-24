#include<avr/io.h>
#include<avr/interrupt.h> // interrupt header file
#include<util/delay.h>

/**
	External Interrupt Program
*/
// Interrupt service Routine for INTO
ISR(INT0_vect) 
{
		
	//_delay_ms(50); // Software Debounce delay
	PORTB ^= 1<<PINB0;
	_delay_ms(50);
	
	
}

int main (void)
{
	DDRB |= 1<< PINB0 | 1<< PINB2; // setn PINB0 and PINB1 as output
	PORTB &= ~(1<< PINB0 | 1<< PINB2);
	
	DDRD &= ~(1<<PIND2); // PIND2 set as input.. This is the INT0 pin to which button is connected
	PORTD |= 1 << PIND2; // push PIND2 to high - internal pull up resisitor- short when button is pressed
	
	GIMSK = 1<<INT0;			// enable interrupt on INTO pinD2
	MCUCR = 1<<ISC01 | 1 << ISC00; // Trigger INTO on rising edge
	
	
	// enable global interrupts
	sei();	
	
	while(1)
	{
		
		PORTB ^= 1 << PINB2;
		_delay_ms(50);
		
	}
}



