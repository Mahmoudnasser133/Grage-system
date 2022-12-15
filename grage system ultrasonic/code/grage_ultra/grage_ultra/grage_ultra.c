/*
 * grage_ultra.c
 *
 * Created: 08-Dec-22 1:14:53 AM
 *  Author: nasser
 */ 


#include <avr/io.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include "LED.h"

#include <avr/interrupt.h>
#include "timer.h"
#include "ultrasonic_sensor.h"


int main(void)
{

	LED_vInit('C',0);
	LED_vInit('C',1);
	DIO_vsetPINDir('D',7,1);
	DIO_vsetPINDir('D',0,1);
	
	unsigned short distance_enter,distance_exit;
	unsigned char enter_flag=0;
	unsigned char exit_flag=0;
	

	while(1)
	{
		
		/************************ Enter ********************************/
		distance_enter=dist('D',7);
		_delay_ms(10);
		
				if ((enter_flag==1) && (distance_enter>20))
				{
					LED_vTurnOff('C',0);
					enter_flag=0;
					timer1_wave_fastPWM(1);
					_delay_ms(500);


				}
				else if((distance_enter<20) && (enter_flag==0))
				{

					LED_vTurnOn('C',0);
					enter_flag=1;
					timer1_wave_fastPWM(-1);
					_delay_ms(1000);
					
				}
	
		/************************ Exit  **************************/
		
		distance_exit=dist('D',0);
		_delay_ms(10);
			
			if ((exit_flag==1) && (distance_exit>20))
			{
				LED_vTurnOff('C',1);
				exit_flag=0;
				timer1_wave_fastPWM_B(-1);
				_delay_ms(500);


			}
			else if((distance_exit<20) && (exit_flag==0))
			{

				LED_vTurnOn('C',1);
				exit_flag=1;
				timer1_wave_fastPWM_B(-1);
				_delay_ms(1000);
				
			}
	

		/************************************************************/
		

		
	}
	

	
}