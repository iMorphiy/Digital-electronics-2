/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
 * 
 * Note:
 *    Peter Fleury's UART library.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Display string without auto linefeed
    lcd_puts("LCD testing");
    // Put string to ringbuffer for transmitting via UART.
    //uart_puts("UART testing\r\n");

    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */

   // ADMUX = ADMUX   |  _BV(MUX0);
    ADCSRA = ADCSRA |  _BV(ADEN);
    ADCSRA = ADCSRA |  _BV(ADIE);
    ADCSRA = ADCSRA |  _BV(ADPS0) |  _BV(ADPS1) |  _BV(ADPS2);
    ADMUX = ADMUX |  _BV(REFS0);

    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // Infinite loop
    for (;;) {
        
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
 ADCSRA = ADCSRA |  _BV(ADSC);
}

/**
 *  Brief: ADC complete; interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    uint16_t value = 0;
    char uart_string[4];
    // Read 10-bit ACD value
    value = ADC;
    itoa(value, uart_string, 10);
    //lcd_puts(uart_string);
   // lcd_putc(' ');
   // uart_puts(uart_string);
    //uart_puts(" ");

   
            if (value>630 && value<670)
               uart_puts("select button is pressed\r\n");
                
                
            if ( value>380 && value<420)
               uart_puts("left button is pressed\r\n");
                    
    
            if (value>80 && value<120)    
               uart_puts("up button is pre pressed\r\n");
                

            if (value>230 && value<270)
               uart_puts("down button  is pressed\r\n");
                
                
             if (value==0)
               uart_puts("right button  is pressed\r\n");
                
            
             
        

}