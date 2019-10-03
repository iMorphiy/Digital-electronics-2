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
//#include <avr-libc.h>
 

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN     PB5
#define GREEN_PIN     PB0
#define BUTTON_PIN     PD2


#define BLINK_DELAY 500
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
    DDRB |= _BV(LED_PIN);           /* DDRB = DDRB or (0010 0000) */
    DDRB |= _BV(GREEN_PIN); 
    DDRD &= ~(1<<BUTTON_PIN);
    PORTD |= _BV(BUTTON_PIN);




    /* Turn LED off */
    PORTB |= _BV(LED_PIN);         /* PORTB = PORTB and (0010 0000) */
    PORTB &= ~_BV(GREEN_PIN);
    
  for(;;) 

  {
    if (bit_is_clear(PIND, BUTTON_PIN))  {

      PORTB^=_BV(LED_PIN);
      PORTB^=_BV(GREEN_PIN);
      _delay_ms(BLINK_DELAY);
    }
    
  }
    /* Infinite loop */
    

    return (0);
}
