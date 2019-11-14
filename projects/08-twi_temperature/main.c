/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2017-10-27
 * Last update: 2019-11-08
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Scan TWI bus for all connected slave devices and transmit info
 *    to UART.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "twi.h"
#include <stdio.h>

#define UART_BAUD_RATE 9600


int main(void)
{
    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // TWI
    twi_init();

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART.
    //uart_puts("\r\n---TWI scanner---");
    //uart_puts("\r\n     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Update state of TWI Finite
 *         State Machine.
 */
ISR(TIMER1_OVF_vect)
{
   
    uint8_t h_int=0;
    uint8_t h_fract=0;
    uint8_t t_int=0;
    uint8_t t_fract=0;

    char string1 [10];

    uint8_t ht_addr = 0x5c; 

    uint8_t response;
   
   

    response = twi_start((ht_addr<<1) + TWI_WRITE);
        
        if(response == 0)
        {
            twi_write(0x00);
        }
        twi_stop();

        response = twi_start((ht_addr<<1) + TWI_READ);
        if(response== 0)
        {
            h_int =     twi_read_ack();
            h_fract =   twi_read_ack();
            t_int =     twi_read_ack();
            t_fract =   twi_read_nack();
        }    
        twi_stop();

    sprintf(string, "H %02d.%02d T:%02d.%02d \r\n", h_int, h_fract, t_int, t_fract);
    uart_puts(string1);
}