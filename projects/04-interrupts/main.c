



#include <avr/io.h>
#include "gpio.h"
#include "timer.h"
<<<<<<< HEAD

#include <avr/interrupt.h>

#define LED_GREEN   PB5
#define LED_RED     PB0


=======
#include <avr/interrupt.h>

//#include <avr-libc.h>
 

/* Define ------------------------------------------------------------*/
#define LED_PIN13  PB5
#define LED_PIN11  PB3
#define LED_PIN8   PB0


  int count=0; 
  
    
>>>>>>> 6ee2dcd3090d8b425010643861d073c53ae7c88f
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

<<<<<<< HEAD
    GPIO_config_output(&DDRB, LED_GREEN);
    GPIO_write(&PORTB, LED_GREEN, PIN_LOW);

    TIM_config_prescaler(TIM0, TIM_PRESC_1024);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    sei();


    for (;;) {



    }

    return (0);
}


ISR(TIMER0_OVF_vect)
{
   GPIO_toggle(PINB, LED_GREEN);
}


ISR(TIMER1_OVF_vect)
{
    GPIO_toggle(PORTB, RED_GREEN);
}
=======
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
>>>>>>> 6ee2dcd3090d8b425010643861d073c53ae7c88f
