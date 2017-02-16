/************************************************************************
*
*     DESCRIPTION
*
*         This file contains initialization and utility routines for
*         UART
*
*     FUNCTIONS
*
*         UART_Init
*         UART_TxChar
*         UART_TxString
*
***********************************************************************/

#include "global.h"

/***********************************************************************
*
*     FUNCTION
*
*         UART_Init
*
*     DESCRIPTION
*
*         This function initializes the UART.         
*
*     INPUTS
*
*         None
*
*     OUTPUTS
*
*         None
*
***********************************************************************/
void UART_Init()
{
    /* Configure Rx pin as input and Tx as output */
    TRISC = 0x80;
    
    /* Asynchronous mode, 8-bit data & enable transmitter */
    TXSTA = 0x24;      
    
    /* 8-bit continous receive enable */
    RCSTA = 0x90;      
    
    /* 9600 Baud rate at 4MHz */
    SPBRG = 25;  
}

/***********************************************************************
*
*     FUNCTION
*
*         UART_TxChar
*
*     DESCRIPTION
*
*         This function transmits a character over the UART.         
*
*     INPUTS
*
*         c - Character to be transmitted
*
*     OUTPUTS
*
*         None
*
***********************************************************************/
void UART_TxChar(char c)
{
    /* Wait till the transmitter register becomes empty */
    while (TXIF == 0);  

    /* Clear transmitter flag */
    TXIF = 0;
    
    /* Transmit the character */
    TXREG = c;
}

/***********************************************************************
*
*     FUNCTION
*
*         UART_TxString
*
*     DESCRIPTION
*
*         This function transmits a string over the UART.         
*
*     INPUTS
*
*         string - Pointer to the string of characters
*
*     OUTPUTS
*
*         None
*
***********************************************************************/
void UART_TxString(const unsigned char *string)
{
    /* Transmit the entire string */
    while(*string)
    {
        UART_TxChar(*string++);
    }
}

