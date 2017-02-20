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

/* Global variable to hold received character. */
char rx_data;

/* Global flag to indicate valid data is present in rx_data. */
char valid_rx_data;

/***********************************************************************
*
*     FUNCTION
*
*         uart_rx_isr
*
*     DESCRIPTION
*
*         This function is the UART RX ISR.         
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
void uart_rx_isr()
{  
    /* If over run error, then reset the receiver. */
    if(OERR)
    {
        CREN = 0;
        CREN = 1;
    }
    
    /* Read the data byte into global variable. */
    rx_data = RCREG;
    
    /* Set the flag to indicate that valid data is available in the RX
     *  register. */
    valid_rx_data = 1;
}

/***********************************************************************
*
*     FUNCTION
*
*         UART_Read
*
*     DESCRIPTION
*
*         This function reads a character from the UART buffer.         
*
*     INPUTS
*
*         rxbyte - pointer to where we return the received character.
*         block - Should we block until a character is received?
*
*     OUTPUTS
*
*         None
*
***********************************************************************/
void UART_Read(char *rxbyte, char block)
{
    /* Check if valid data is available in the UART buffer. */
    if(valid_rx_data == 0)
    {
        /* Check if we need to wait for data. */
        if(block)
        {
            while(valid_rx_data == 0);
            
            /* Get the received data. */
            *rxbyte = rx_data;
            
            /* Reset the valid data flag. */
            valid_rx_data = 0;
        }
        else
        {
            *rxbyte = 0x00;
        }
    }
    else
    {
        /* Get the received data. */
        *rxbyte = rx_data;
        
        /* Reset the valid data flag. */
        valid_rx_data = 0;
    }
}
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
    
    /* 8-bit continuous receive enable */
    RCSTA = 0x90;      
    
    /* Enable RX interrupt. */
    RCIE = 1;
    
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
