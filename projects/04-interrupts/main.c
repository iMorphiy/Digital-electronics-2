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
#include "timer.h"
#include <avr/interrupt.h>

//#include <avr-libc.h>
 

/* Define ------------------------------------------------------------*/
#define LED_PIN13  PB5
#define LED_PIN11  PB3
#define LED_PIN8   PB0


  int count=0; 
  
    
int main(void)
{
    
    GPIO_config_output(&DDRB, LED_PIN13);
    GPIO_write(&PORTB, LED_PIN13, 1);

    GPIO_config_output(&DDRB, LED_PIN11);
    GPIO_write(&PORTB, LED_PIN11, 1);

    GPIO_config_output(&DDRB, LED_PIN8);
    GPIO_write(&PORTB, LED_PIN8, 1);


    /* Set Timer0 */
    TIM_config_prescaler(TIM0, TIM_PRESC_1);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    /* Set Timer1 */
    TIM_config_prescaler(TIM1, TIM_PRESC_1);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    /* Set Timer2 */
    TIM_config_prescaler(TIM2, TIM_PRESC_1);
    TIM_config_interrupt(TIM2, TIM_OVERFLOW_ENABLE);

    /* Enable interrupts by setting the global interrupt mask */
   sei();

    for (;;) {

    }

    return (0);
}

ISR(TIMER0_OVF_vect)
{
    
 
 count++;
 if (count > 100)
 {
    GPIO_toggle(&PORTB, LED_PIN13);
 }
    
}

ISR(TIMER1_OVF_vect)
{
     count++;
 if (count > 100)
 {
    GPIO_toggle(&PORTB, LED_PIN11);
 }
}

ISR(TIMER2_OVF_vect)
{
     count++;
 if (count > 100)
 {
    GPIO_toggle(&PORTB, LED_PIN8);
 }
}
