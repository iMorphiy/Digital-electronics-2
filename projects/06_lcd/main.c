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

volatile uint8_t i =0;
void BAR(uint8_t count_to);
int main(void)
{
    lcd_init(LCD_DISP_ON);

    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    
    uint8_t customChar1[] = {
  0x01,
  0x02,
  0x06,
  0x0C,
  0x1F,
  0x06,
  0x04,
  0x08,
  0x0E,
  0x1F,
  0x11,
  0x11,
  0x11,
  0x11,
  0x11,
  0x1F,

  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  
  0x14,
  0x14,
  0x14,
  0x14,
  0x14,
  0x14,
  0x14,
  0x14, 

  0x15,
  0x15,
  0x15,
  0x15,
  0x15,
  0x15,
  0x15,
  0x15,


};

lcd_command(1<<LCD_CGRAM);
    for (uint8_t j=0; j<40; j++)
        {
         lcd_data(customChar1 [j]);
        }

/* Counter=>-DEC:-------------------------------*/
/* $---------0b---------------------------------*/

    // lcd_puts ("Counter=>");
    // lcd_gotoxy (9 , 0);  
    
    // lcd_puts ("DEC:");
    
    // lcd_gotoxy (0 , 1);
    // lcd_puts ("$");
    // lcd_gotoxy (6, 1);
    // lcd_puts ("0b");

   sei();
    
 for(;;) 
 {

    //(10);
     
 }  
    return (0);
}


ISR(TIMER1_OVF_vect)
{   
if(i<48){
    i++;
    BAR(i);
    // char char_hex[3];
    // char char_bin[9];
    // char char_dec[4];
    // lcd_gotoxy (13 , 0);
    // lcd_puts("   ");
    // lcd_gotoxy (13 , 0);
    // lcd_puts(itoa(i, char_dec, 10));
    // lcd_gotoxy (1 , 1);
    // lcd_puts(itoa(i, char_hex, 16));
    // lcd_gotoxy (8, 1);
    // lcd_puts (itoa(i, char_bin, 2));
    }
    
    else {
    i=0;
    lcd_clrscr ();
    }
    
    
}

void BAR(uint8_t count_to)
{  
    
    char prcent[4];
    uint8_t bar = count_to/3;
    uint8_t rest = count_to%3;
    uint8_t state =(count_to*100)/48;
    lcd_gotoxy (12, 0);
    itoa(state, prcent, 10);
    lcd_puts(prcent);
    lcd_gotoxy (15, 0);
    lcd_puts("%");
    for (uint8_t k = 0; k < bar; k++)
    {
        
        if(count_to>2){
        lcd_gotoxy (k, 1);
        lcd_putc(0x04);
        if (rest!=0 && k+1==bar){
            if(rest==2)
            {
                lcd_gotoxy (k+1, 1);
                lcd_putc(0x03);
            }
            else
            {   
                lcd_gotoxy (k+1, 1);
                lcd_putc(0x02);
            }
            
            }
        }        
    }

    if(count_to==2){
        lcd_gotoxy (0, 1);
        lcd_putc(0x03);
    }
    if(count_to==1)
     {   
        lcd_gotoxy (0, 1);
        lcd_putc(0x02);
            
        }
   

}