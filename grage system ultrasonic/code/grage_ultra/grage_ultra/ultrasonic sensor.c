#include <avr/io.h>
#include "ultrasonic_sensor.h"
#include "DIO.h"
#define  F_CPU 8000000UL
#include <util/delay.h>

	


unsigned short dist(unsigned port,unsigned pin)
{
	unsigned short a1,b1,high1,distance;
	DIO_vsetPINDir(port,pin,1);
	a1=b1=high1=distance=0;
	TCCR1A = 0;
	TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag)  */
	DIO_write(port,pin,1);
	_delay_us(50);
	DIO_write(port,pin,0);
	
	//TCCR1B = 0xc1;  	/* Rising edge, no prescaler , noise canceler*/
	TCCR1B= 0xc2;	    /* Rising edge, prescaler = 8 , noise canceler*/
	while ((TIFR&(1<<ICF1)) == 0);
	a1 = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */
	//TCCR1B = 0x81;  	/* Falling edge, no prescaler ,noise canceler*/
	TCCR1B = 0x82;   /* Falling edge, prescaler=8 ,noise canceler*/
	while ((TIFR&(1<<ICF1)) == 0);
	b1 = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */
	TCNT1=0;
	TCCR1B = 0;  		/* Stop the timer */
	high1=b1-a1;
	distance=((high1*34600)/((F_CPU/8)*2)) ;//prescaler =8
	
	return distance;
}


