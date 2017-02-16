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

void main(void)
{
    unsigned int adc_val;
    char string[20];
    
    TRISD=0X00;
    PORTD=0X00;      

    /* Initialize the UART controller. */
    UART_Init();
    
    /* Initialize the ADC controller. */
    ADC_Init();
    
    UART_TxString("Starting Test application\n\r");

    while(1)
    {
        adc_val = ADC_StartConversion(0);        
        
        sprintf(string, "ADC Value = %f\n\r", (double) (adc_val * 4.8875) / 1000);
        
        UART_TxString(string);
        
        UART_TxString("Turning LEDs OFF\n\r");
        PORTD=0XFF;
        __delay_ms(100);

       UART_TxString("Turning LEDs ON\n\r");
       PORTD=0X00;
       __delay_ms(100);
    }

    return;
}
