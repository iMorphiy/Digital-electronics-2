/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"

//#include <avr-libc.h>
 

/* Define ------------------------------------------------------------*/
#define LED_PIN     PB5
#define GREEN_PIN   PB0
#define BUTTON_PIN  PD2
#define BLINK_DELAY 250
    
  
    
int main(void)
{

 GPIO_config_output(&DDRB, GREEN_PIN);
 GPIO_config_output(&DDRB, LED_PIN);
 GPIO_config_input_nopull(&DDRD, BUTTON_PIN);
          
 for(;;)
{	
if(GPIO_read(&PIND, BUTTON_PIN)==0)
	GPIO_write(&PORTB, GREEN_PIN, 1);
else
  	GPIO_write(&PORTB, GREEN_PIN, 0);
}

return (0);
}