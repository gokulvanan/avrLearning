#include<avr/io.h>
#include<avr/interrupt.h> // interrupt header file

// Here polling of TCNT1 will be avoided
// OCR1A  is used to hold 15625 value for prescalling
// Here alternative to making TCNT1=0 we modify TCCR1B - WGM12 (wave form generation mode) is set to CTC mode.
// CTC = clear timer on compare mode that would reset  when TCNT compares to OCR1A
// sei() -- enables global interrupts
// TIMSK reigsiter used to enable interrupts with OCR1A
int main (void)
{
	// enable global interrupts
	sei();
	
	// initialize the ports for the LED
	DDRB |= (1 << PINB0) ; // mark B0 as output
	PORTB &= ~(1 << PINB0 ) ; // keep B0 low at start
	TCCR1B  |= (1 << CS10) | (1 << CS11); // count as per MCU clock/64 = 1000000/64 = 15625 
	TCCR1B |= 1<< WGM12; // wave form gernation mode.. 1 rerpsent 16btis.. 2 is more than one mode
	TIMSK |= 1<< OCIE1A; //this maps timer Interrupt mask to associate with OCR1A
	OCR1A = 15624; // The value when TCNT1 reaches it reset to 0.
	// note WGM setup enables TCNT to reseset to 0 when it reaches value compare to OCR1A
	// TIMSK with OCIE1A maps OCR1A as the register to compare to reset to 0 else it could also be OCR1B with OCIE1B
	
	while(1)
	{
	
	}
}

// Interrupt service routine
// Name of ISR arg appears important it identifies the type of interrupt for executing this subroutine
// sample ISR names are:
/*
ISR(SPI_STC_vect){}; //SPI sertial transfer complete
ISR(TIMER0_COMP_vect){}; //TCNT0 compare match A
ISR(TIMER0_OVF_vect){}; //TCNT0 overflow
ISR(INT2_vect){}; //External Interuupt Request 2
*/
ISR(TIMER1_COMPA_vect) 
{
	PORTB ^= 1<<PINB0;
}