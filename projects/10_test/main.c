#include <stdlib.h>         
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "twi.h"
#include <stdio.h>


#define UART_BAUD_RATE 9600

//static int FILE mystduot = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{

  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

  twi_init();

  TIM_config_prescaler(TIM1, TIM_PRESC_256);
  TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

  sei();

  for (;;)
  {

  }

  return (0);
}


ISR(TIMER1_OVF_vect)
{   
  
  uint8_t byte_sec = 0;
  uint8_t byte_min = 0;
  uint8_t byte_hour = 0;
  uint8_t rtc_addr = 0x68;
  uint8_t ht_addr = 0x5c;
  uint8_t response;

  uint8_t h_int=0;
  uint8_t h_fract=0;
  uint8_t t_int=0;
  uint8_t t_fract=0;

response = twi_start((rtc_addr<<1) + TWI_WRITE);
        
  if(response == 0)
  {
    twi_write(0x00);
  }
  twi_stop();

  response = twi_start((rtc_addr<<1) + TWI_READ);
       
  if(response == 0)
  {
    byte_sec = twi_read_ack();
    byte_min = twi_read_ack();      
    byte_hour = twi_read_nack();
  }    
  twi_stop();
  

  uint8_t seconds=(((byte_sec&~0b00001111)>>4)*10+(byte_sec&~0b01110000));
  uint8_t minutes=(((byte_min&~0b00001111)>>4)*10+(byte_min&~0b01110000));
  uint8_t hours=(((byte_hour&~0b00001111)>>4)*10+(byte_hour&~0b01110000));

  char string1 [20];
  sprintf(string1, "%02d:%02d:%02d   ",hours, minutes, seconds);
  
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

  char string [15];
  sprintf(string, "H: %d.%d T: %d.%d C \r\n", h_int, h_fract, t_int, t_fract);
  
  uart_puts(string1);  
  uart_puts(string);

}