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
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "timer.h"
#include "segment.h"
#include <avr/interrupt.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_D1          PB5
#define BTN_S1          PC1 // PCINT 9
#define BTN_S2          PC2 // PCINT 10
#define BTN_S3          PC3 // PCINT 11

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on 7-segment display.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    /* D1 led */
    // TODO: Configure D1 led at Multi-Function Shield
    GPIO_config_output(&DDRB, LED_D1);
    //GPIO_write(&PINB, LED_D1, 1);
    // TODO: Configure Pin Change Interrupts 11, 10, and 9

    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PCINT9); 
    //|_BV(PCINT10) |_BV(PCINT11);
    /* 7-segment display interface */

    GPIO_config_output(&DDRB, SEGMENT_DATA);
    GPIO_config_output(&DDRD, SEGMENT_CLK);
    GPIO_config_output(&DDRD, SEGMENT_LATCH);

    GPIO_config_input_nopull(&DDRC, BTN_S1);
    GPIO_config_input_nopull(&DDRC, BTN_S2);
    GPIO_config_input_nopull(&DDRC, BTN_S3);

    GPIO_write(&PORTB, SEGMENT_DATA, 0);
    GPIO_write(&PORTD, SEGMENT_CLK, 0);
    GPIO_write(&PORTD, SEGMENT_LATCH, 0);
    // TODO: Configure 7-segment display pins
    //TIM_config_prescaler(TIM1, TIM_PRESC_64);
    //TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    /* Enable interrupts by setting the global interrupt mask */
    sei();

    /* Infinite loop */
    for (;;) {

     
       for(uint8_t a=0; a<=9; a++){
           SEG_putc(a, 0);
           _delay_ms(200);
       }

    }

    return (0);
}

ISR(PCINT1_vect)
{
    GPIO_toggle(&PORTB, LED_D1);
}
