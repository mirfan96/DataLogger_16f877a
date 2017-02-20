
/************************************************************************
*
*     DESCRIPTION
*
*         This file contains the global interrupt handler.
*
*     FUNCTIONS
*
*         ISR_Handler
*
***********************************************************************/

#include "global.h"

/***********************************************************************
*
*     FUNCTION
*
*         ISR_Handler
*
*     DESCRIPTION
*
*         This function is the PIC ISR.         
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
void interrupt timer_isr()
{  
    /* Check if the timer1 overflow flag is set. */
    if(TMR1IF==1)
    {
        /* Invoke the timer1 ISR routine */
        (void)timer1_isr();
        
        /* Clear the timer overflow flag. */
        TMR1IF=0;
    }
    
    /* Check if UART RX interrupt. */
    if(RCIF)
    {
        (void)uart_rx_isr();
    }
}
