/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-16
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Decimal counter with data output on LCD display.
 * 
 * Note:
 *    Modified version of Peter Fleury's LCD library with R/W pin 
 *    connected to GND. Newline symbol "\n" is not implemented, use
 *    lcd_gotoxy() function instead.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>             // itoa() function
#include "timer.h"
#include "lcd.h"
#include <util/delay.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on LCD display.
 *  Input:  None
 *  Return: None
 */
 char char_hex[] = "";
 char char_bin[] = "";
 char char_dec[] = "";
    uint8_t i =0;
 int main(void)

{
    lcd_init(LCD_DISP_ON);

    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    
    lcd_puts ("Counter:");
    lcd_gotoxy (9 , 0);  
    lcd_gotoxy (0 , 1);
    lcd_puts ("$");
    lcd_gotoxy (6, 1);
    lcd_puts ("0b");
  
    sei();

 for(;;)   
 {

 }

    // Will never reach this
    return (0);
}


ISR(TIMER1_OVF_vect)
{   
    i++;
    lcd_gotoxy (9 , 0);
    lcd_puts(itoa(i, char_dec, 10));
    lcd_gotoxy (0 , 1);
    lcd_puts(itoa(i, char_hex, 16));
    lcd_gotoxy (6, 1);
    lcd_puts (itoa(i, char_hex, 2));
     
}