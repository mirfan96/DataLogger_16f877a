/************************************************************************
*
*     DESCRIPTION
*
*         This file contains initialization and utility routines for
*         TImer
*
*     FUNCTIONS
*
*         timer_isr
*         ADC_StartConversion
*
***********************************************************************/

#include "global.h"

/* Global variables. */
char timer_high_val = 0,
     timer_low_val  = 0;

/***********************************************************************
*
*     FUNCTION
*
*         timer1_isr
*
*     DESCRIPTION
*
*         This function is the timer1 ISR.         
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
void timer1_isr()
{  
    /* Reload the timer. */
    TMR1H = timer_high_val;
    TMR1L = timer_low_val;
        
#if (defined(_USER_TIMER_FUNC) && (_USER_TIMER_FUNC == true))
    user_timer_callback();
#endif
}

/***********************************************************************
*
*     FUNCTION
*
*         TIMER_init
*
*     DESCRIPTION
*
*         This function initializes the timer1.         
*
*     INPUTS
*
*         time_period - Timer period of the timer1 in milliseconds
*
*     OUTPUTS
*
*         None
*
***********************************************************************/
char TIMER_init(char time_period)
{
    unsigned int timer_val;
    
    if(time_period > 65)
    {
        /* We can not generate a time period of more than 65ms. */
        return 1;
    }
    
    /* Disable the timer, use internal (Fosc / 4) clock, and 1:1 prescalar */
    T1CON = 0;
    
    timer_val = 65535 - ( (_XTAL_FREQ / 4000 ) * time_period);
    
    timer_high_val = (timer_val & 0xFF00) >> 8;
    timer_low_val  = (timer_val & 0xFF);
    
    TMR1H = timer_high_val;
    TMR1L = timer_low_val;
    
    return 0;
}

/***********************************************************************
*
*     FUNCTION
*
*         TIMER_Start
*
*     DESCRIPTION
*
*         This function starts the timer1.         
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
void TIMER_Start()
{
    /* Enable timer interrupt bit in PIE1 register. */
    TMR1IE = 1;            
    
    /* Start Timer1. */
    TMR1ON = 1;
}