#ifndef ButtonPress // ensures this is loaded only once (if not defined)

#define ButtonPress // defines the name of this header file

#include <avr/io.h> // utility need for bit_is_cleared check


/*
 Button press header file
*/

// function prototypes declared here

char ButtonPressed(int buttonNo, unsigned char pinOfButton, unsigned char portBit,int cf_th);

//requires #defined nofButtons 10 to be added at before including this header fiel
char press[noOfButtons];
int pressed_cf[noOfButtons];
int released_cf[noOfButtons];
		

char ButtonPressed(int buttonNo,unsigned char pinOfButton, unsigned char portBit,int cf_th)
{
	if(bit_is_clear(pinOfButton,portBit))
	{
	
		if (pressed_cf[buttonNo]++ > cf_th)
		{
			if (press[buttonNo] == 0 ) 
			{
				press[buttonNo] = 1;
				return 1;// true case 
			}
			pressed_cf[buttonNo] = 0;
		}
	}
	else
	{
		if(released_cf[buttonNo]++ > cf_th)
		{
			press[buttonNo]=0;
			released_cf[buttonNo]=0;
		}
	}
	return 0; // default return case
}

#endif