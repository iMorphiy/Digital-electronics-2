
#include <avr/io.h>
#include "gpio.h"



void fsm_random(void);
extern uint8_t pulse_asm(uint8_t current);

int main (void)                                    
{
    GPIO_config_output(&DDRB , PB5);
    
    for (;;) 
    {
        pulse_asm(10) ; 
    }
    return (0);
}