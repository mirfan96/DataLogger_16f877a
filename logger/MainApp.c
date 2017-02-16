/*
 * File:   MainApp.c
 * Author: mirfan
 *
 * Created on February 15, 2017, 7:36 PM
 */

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include "global.h"
#include <stdio.h>

unsigned int value = 0;

void user_timer_callback(void)
{
    value++;
}

void main()
{    
    char string[75];
    unsigned int adc_val;
    
    /* Configure PORTD as output to blink the LEDs. */
    TRISD=0x00;

    /* Initialize the UART controller. */
    UART_Init();
    
    /* Initialize the ADC controller. */
    ADC_Init();
    
    /* Initialize the timer. */
    if ( TIMER_init(10) )
        while(1);
    
    /* Kick start the timer. */
    TIMER_Start();
    
    while(1)
    {
        adc_val = ADC_StartConversion(0);        
        
        sprintf(string, "ADC Value = \t\t%0.3f\n\rTimer Interrupts = \t%d\n\r", (double) (adc_val * 4.8875) / 1000, value);
        UART_TxString(string);
        
    }
}
