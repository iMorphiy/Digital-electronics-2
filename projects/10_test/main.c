#include <stdlib.h>         
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "twi.h"


#define UART_BAUD_RATE 9600

int main(void)
{

  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

  TIM_config_prescaler(TIM1, TIM_PRESC_8);
  TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

  sei();

  for (;;)
  {

  }

  return (0);
}


ISR(TIMER1_OVF_vect)
{   
  
  uint8_t byte_sec = 0b01010100;
  uint8_t byte_min = 0b00110000;
  uint8_t byte_hour = 0b00010001;

  char string [3];

  uint8_t seconds=(((byte_sec&~0b00001111)>>4)*10+(byte_sec&~0b01110000));
  uint8_t minutes=(((byte_min&~0b00001111)>>4)*10+(byte_min&~0b01110000));
  uint8_t hours=(((byte_hour&~0b00001111)>>4)*10+(byte_hour&~0b01110000));

  uart_puts(itoa(hours, string, 10));
  uart_puts(":");
  uart_puts(itoa(minutes, string, 10));
  uart_puts(":");
  uart_puts(itoa(seconds, string, 10));
  uart_puts("\r\n");
}