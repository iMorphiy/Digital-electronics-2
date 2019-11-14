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



/* Typedef -----------------------------------------------------------*/
typedef enum {
    IDLE_STATE = 1,
    TRY_STATE,
    ACK_STATE
} state_t;

/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
state_t current_state = IDLE_STATE;

/* Function prototypes -----------------------------------------------*/
void fsm_twi_scanner(void);

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Test all TWI slave addresses and scan 
 *          connected devices.
 *  Input:  None
 *  Return: None
 */
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
   // fsm_twi_scanner();
    
    // uint8_t h_int=0;
    // uint8_t h_fract=0;
    // uint8_t t_int=0;
    // uint8_t t_fract=0;

    uint8_t seconds=0;
   // uint8_t minutes=0;
    uint8_t hours=0;
    uint8_t sec=0;
    
    // char H_int[3];
    // char H_fract[3];
    // char T_int[3];
    // char T_fract[3];

    char RTC_seconds[3];
    char RTC_minutes[3];
    char RTC_hours[3];
   
    //uint8_t ht_addr = 0x5c; 
    uint8_t rtc_addr = 0x68; 
    uint8_t response;
    uint8_t shift=0;
    uint8_t shift1=0;


    
    uint8_t bitmasc = 0b01110000;
    uint8_t bitmasc2= 0b00001111;
   

    // response = twi_start((ht_addr<<1) + TWI_WRITE);
        
    //     if(response == 0)
    //     {
    //         twi_writbitmasce(0x00);
    //     }bitmasc
    //     twi_stop();bitmasc

    //     response = tbitmascwi_start((ht_addr<<1) + TWI_READ);
    //     if(response bitmasc== 0)
    //     {
    //         h_int =     twi_read_ack();
    //         h_fract =   twi_read_ack();
    //         t_int =     twi_read_ack();
    //         t_fract =   twi_read_nack();
    //     }    
    //     twi_stop();
    
    response = twi_start((rtc_addr<<1) + TWI_WRITE);
        
        if(response == 0){

           twi_write(0x00);
        }
        twi_stop();

    response = twi_start((rtc_addr<<1) + TWI_READ);
       
        if(response == 0)
        {
            seconds = twi_read_ack();

        shift = seconds&bitmasc;
        shift =(shift>>4);
        shift1=seconds&bitmasc2;
        sec=(10*shift)+shift1;

           // minutes = twi_read_ack();          
            hours =   twi_read_nack();
        }    
        twi_stop();

    itoa(sec, RTC_seconds, 10);
    itoa(sec, RTC_minutes, 10);
    itoa(hours, RTC_hours, 10);
     
     
    // itoa(h_int, H_int, 10);
    // itoa(h_fract, H_fract, 10);
    // itoa(t_int, T_int, 10);
    // itoa(t_fract, T_fract, 10);
     
    //uart_puts(RTC_hours);
    //uart_puts(":"); 
    //uart_puts(RTC_minutes);
    
    uart_puts(RTC_seconds);
    uart_puts("\r\n"); 



    //  uart_puts("HUM: "); 
    //  uart_puts(H_int);
    //  uart_puts("."); 
    //  uart_puts(H_fract);
    //  uart_puts("   TEMP: "); 
    //  uart_puts(T_int);
    //  uart_puts("."); 
    //  uart_puts(T_fract);
    //  uart_puts("\r\n"); 
      

}

/**
 *  Brief: Test one TWI address.
 */
void fsm_twi_scanner(void)
{
    static uint8_t addr = 0;
    uint8_t status;
    char uart_string[3];
    uint8_t i = 1;

    switch (current_state) {
    case IDLE_STATE:
        if (addr < 128) {
            itoa(addr, uart_string, 16);
            uart_puts("\r\n");
            uart_puts(uart_string);
            current_state = TRY_STATE;
        }
        break;

    // Transmit TWI slave address and check status
    case TRY_STATE:
        status = twi_start((addr<<1) + TWI_WRITE);
        twi_stop();

        if (status == 0) {
            current_state = ACK_STATE;
        } else {
            addr++;
            current_state = IDLE_STATE;
            uart_puts(" NOTHING");
        }
        break;

    // Slave ACK received
    case ACK_STATE:
        //uart_puts(" <-ADDRESS OF SLAVE DETECTED");
        
        i=twi_start(57);
         if (i==0){
             uart_puts("Score");
         }
         else
         uart_puts("no responce");
        addr++;
        current_state = IDLE_STATE;
        break;

    default:
        current_state = IDLE_STATE;
    }
}
