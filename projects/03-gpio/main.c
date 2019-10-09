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
 

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN     PB5
#define GREEN_PIN     PB0
#define BUTTON_PIN     PD3


#define BLINK_DELAY 250
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    /* Set output pin */
   
    GPIO_config_output(&DDRB, LED_PIN);           /* DDRB = DDRB or (0010 0000) */
    GPIO_config_output(&DDRB, GREEN_PIN); 
    





    /* Turn LED off */
    
    GPIO_write(&PORTB, LED_PIN, 1);     /* PORTB = PORTB and (0010 0000) */
    GPIO_write(&PORTB, GREEN_PIN, 0);  
    
  for(;;) 

  {
   

      //GPIO_toggle(&PORTB, LED_PIN); /// TOTO JE NOVE
    // GPIO_toggle(&PORTB, GREEN_PIN); ///
    //  _delay_ms(BLINK_DELAY);
    
    if(GPIO_read(&PIND, BUTTON_PIN)==1) 
     {
       GPIO_write(&PORTB, LED_PIN, 1);
     }
       else {
         GPIO_write(&PORTB, LED_PIN, 0);
       }
       
  }
  
    

    return (0);
}
