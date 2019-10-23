



#include <avr/io.h>
#include "gpio.h"
#include "timer.h"

#include <avr/interrupt.h>

#define LED_GREEN   PB5
#define LED_RED     PB0


int main(void)
{

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