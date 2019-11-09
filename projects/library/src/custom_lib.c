#include <avr/io.h>
#include <stdlib.h> 
#include "custom_lib.h"
#include "lcd.h"


void BAR(uint8_t value)
{  
        uint8_t customChar1[] = {
/* -------lightning symbol 0x00----------------------------------------------*/
  0x01,
  0x02,
  0x06,
  0x0C,
  0x1F,
  0x06,
  0x04,
  0x08,
/* -------battery symbol 0x01----------------------------------------------*/
  0x0E,
  0x1F,
  0x11,
  0x11,
  0x11,
  0x11,
  0x11,
  0x1F,
/* -------| bar symbol 0x02----------------------------------------------*/
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  /* -------|| bar symbol 0x03----------------------------------------------*/
  0x14,
  0x14,
  0x14,
  0x14,
  0x14,
  0x14,
  0x14,
  0x14, 
  /* -------||| bar symbol 0x04----------------------------------------------*/
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

    char prcent[2];
    uint8_t state =(value*48)/100;
    uint8_t bar = state/3;
    uint8_t rest = state%3;
    
    lcd_gotoxy (12, 0);
    itoa(value, prcent, 10);
    lcd_puts(prcent);
    lcd_gotoxy (15, 0);
    lcd_puts("%");
    for (uint8_t k = 0; k < bar; k++)
    {       
        if(state>2)
        {
            lcd_gotoxy (k, 1);
            lcd_putc(0x04);
            if (rest!=0 && k+1==bar)
            {
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

    if(state==2)
        {
        lcd_gotoxy (0, 1);
        lcd_putc(0x03);
        }
    if(state==1)
        {   
        lcd_gotoxy (0, 1);
        lcd_putc(0x02);            
        }
   

}