#include "gpio.h"

void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name |= _BV(pin_num);

}

void GPIO_write(volatile uint8_t *reg_name, uint8_t pin_num, uint8_t pin_val)
{



if (pin_val==0)
     *reg_name &= ~_BV(pin_num); 
else 
    *reg_name |= _BV(pin_num);
}


void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num)

{
    *reg_name^=_BV(pin_num);
}
uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num)

{

    if (bit_is_set(reg_name, pin_num))  

     return(1);
     else
     return(0);
    
}