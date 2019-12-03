/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"
#include "timer.h"


/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define BUZ_PIN  PD3

void BZR(uint16_t dist);
volatile uint16_t i=0;
int main(void)
{

  DDRD |= _BV(BUZ_PIN);           
  PORTD &= ~_BV(BUZ_PIN);       



  TIM_config_prescaler(TIM2, TIM_PRESC_8);
  TIM_config_interrupt(TIM2, TIM_OVERFLOW_ENABLE);  
sei();
    for (;;)
    {       
       
    }
    return (0);
}


ISR(TIMER2_OVF_vect)
{
  BZR(10);

}



void BZR(uint16_t dist)
{
uint16_t delay=0;
uint16_t  freq=0;
  
 if (dist<=400 && dist>200) { freq=20; delay=6000; }
else if (dist<=200 && dist>70) { freq=19; delay=5650; }
else if (dist<=70 && dist>25) { freq=16; delay=4600; }
else if (dist<=25 && dist>18) { freq=15; delay=4250; }
else if (dist<=18 && dist>14) { freq=14; delay=3900; }
else if (dist<=14 && dist>11) { freq=13; delay=3550; }
else if (dist<=11 && dist>10) { freq=12; delay=3200; }
else if (dist<=10 && dist>9) { freq=11; delay=2850; }
else if (dist<=9 && dist>8) { freq=10; delay=2500; }
else if (dist<=8 && dist>7) { freq=9; delay=2150; }
else if (dist<=7 && dist>6) { freq=8; delay=1800; }
else if (dist<=6 && dist>5) { freq=7; delay=1450; }
else if (dist<=5 && dist>4) { freq=6; delay=1100; }
else if (dist<=4 && dist>3) { freq=5; delay=750; }
else if (dist<=3 && dist>2) { freq=4; delay=400; }
else { freq=3; delay=0; }

  i++;
  if (i%freq==0 && i<995){
  
   GPIO_write(&PORTD, PD3, 1);
   GPIO_write(&PORTD, PD3, 0);
   _delay_us(10);
   GPIO_write(&PORTD, PD3, 1);
    
   
  }
else if(i==1000+delay)
i=0;
}
