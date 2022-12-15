/*
 * ultrasonic_sensor.c
 *
 * Created: 08-Dec-22 12:35:21 AM
 *  Author: nasser
 */ 
#include <avr/io.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"
#include "ultrasonic_sensor.h"

unsigned short ultrasonic_distance(void)
{
	
		unsigned short a,b,high,distance;
			DIO_vsetPINDir('D',7,1);
		TCCR1A = 0;
		TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag)  */
		DIO_write('D',7,1);
		_delay_us(50);
		DIO_write('D',7,0);
		
		//TCCR1B = 0xc1;  	/* Rising edge, no prescaler , noise canceler*/
		TCCR1B= 0xc2;	    /* Rising edge, prescaler = 8 , noise canceler*/
		while ((TIFR&(1<<ICF1)) == 0);
		a = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		//TCCR1B = 0x81;  	/* Falling edge, no prescaler ,noise canceler*/
		TCCR1B = 0x82;   /* Falling edge, prescaler=8 ,noise canceler*/
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		TCNT1=0;
		TCCR1B = 0;  		/* Stop the timer */
		high=b-a;
		distance=((high*34600)/((F_CPU/8)*2)) ;//prescaler =8;
		a=b=high=0;
		return distance;
	
	
}
