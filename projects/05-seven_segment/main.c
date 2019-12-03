/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-11
 * Last update: 2019-10-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Decimal counter with data display on 7-segment display.
 * TODO: Create and test functions to operate a 7-segment display using
 *       shift registers.
 * NOTE: Store segment.c and segment.h files in library/src and 
 *       library/inc folders.
 */

/* Includes ----------------------------------------------------------*/

#include <util/delay.h>
#include "gpio.h"
#include "timer.h"
#include "segment.h"



int main(void)
{
    GPIO_config_output(&DDRB, SEGMENT_DATA);
    GPIO_config_output(&DDRD, SEGMENT_CLK);
    GPIO_config_output(&DDRD, SEGMENT_LATCH);
    GPIO_config_output(&DDRD, PD4);

    DDRB |= _BV(SEGMENT_DATA);
    PORTB &= ~_BV(SEGMENT_DATA);
    DDRB |= _BV(SEGMENT_CLK);
    PORTB &= ~_BV(SEGMENT_CLK);
    DDRB |= _BV(SEGMENT_DATA);
    PORTB &= ~_BV(SEGMENT_DATA);

    GPIO_write(&PORTB, SEGMENT_DATA, 0);
    GPIO_write(&PORTD, SEGMENT_CLK, 0);
    GPIO_write(&PORTD, SEGMENT_LATCH, 0);

    for (;;) {
    double floating = 3.40;
    double dec;
    double fractional = modf(floating, &dec);
    fractional = fractional/0.1;  
    float t = 0.5;
    
    four_dig_print(84.7);  
    }

    return (0);
}

