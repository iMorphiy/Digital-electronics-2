#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"
#include "uart.h"
#include "timer.h"
#include "segment.h"

#define S_velosity 340 / 10
#define TRIGER_PIN PB1
#define TRIGER 9600
#define UART_BAUD_RATE 9600

float ECHO_time = 0;
float distance = 0;
uint16_t distance_int = 0;
uint16_t distance_decimal = 0;
uint16_t ticks_rise = 0;
uint16_t ticks_fall = 0;
uint8_t count = 0;
char string[5];

typedef enum {
  UP,
  DOWN
}
state;

state current_state = DOWN;
state next_state = UP;

int main() {

  TIM_config_prescaler(TIM0, TIM_PRESC_1);
  TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

  TIM_config_prescaler(TIM1, TIM_PRESC_256);
  TIMSK1 |= _BV(ICIE1);
  TCCR1B |= _BV(ICES1) | _BV(ICNC1);

  GPIO_config_input_nopull( &DDRB, TRIGER_PIN);

  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

  sei();

  for (;;) {

    if (current_state == DOWN) {
      cli();
      if (ticks_fall > ticks_rise) {
        ECHO_time = (float)(ticks_fall - ticks_rise) / (float)(F_CPU / 256) * 1000000;
      } 
	  else
        ECHO_time = (float)((65535 - ticks_rise) + ticks_fall) / (float)(F_CPU / 256) * 1000000;

      distance = ((float) S_velosity * (float) ECHO_time)/(float) 2000;
      distance_int = (uint16_t) distance;
      distance_decimal = (uint16_t)((((float) distance - (float) distance_int) * 1000)) / 100;
      
	  
      sprintf(string, "%u.%u", distance_int, distance_decimal);
	  sei();
    }

    if (distance_int < 400) {
      	uint16_t i = atoi(string);
      four_dig_print(i);
    }	
  }

  return 0;
}

ISR(TIMER1_CAPT_vect) {

  if (next_state == UP) {
    ticks_rise = ICR1L;
    ticks_rise |= (ICR1H << 8);
    TCCR1B &= ~_BV(ICES1);
    current_state = UP;
    next_state = DOWN;

  } else {
    ticks_fall = ICR1L;
    ticks_fall |= (ICR1H << 8);
    TCCR1B |= _BV(ICES1);

    current_state = DOWN;
    next_state = UP;
  }
}

ISR(TIMER0_OVF_vect) {

  cli();

  count++;
  if (count == 1)
    GPIO_write(&PORTB, TRIGER_PIN, 1);
  if (count == 2)
    GPIO_write(&PORTB, TRIGER_PIN, 0);
  if (count == 700)
    count = 0;

  sei();
}