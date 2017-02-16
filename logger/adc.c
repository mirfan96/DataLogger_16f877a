/************************************************************************
*
*     DESCRIPTION
*
*         This file contains initialization and utility routines for
*         ADC
*
*     FUNCTIONS
*
*         ADC_Init
*         ADC_StartConversion
*
***********************************************************************/

#include "global.h"

/***********************************************************************
*
*     FUNCTION
*
*         ADC_Init
*
*     DESCRIPTION
*
*         This function initializes the ADC.         
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
void ADC_Init()
 {
    /* Sampling frequency = osc_freq / 2, ADC off initially. */
    ADCON0 = 0x00;
    
    /* All pins are configured as ADC and the result is right justified. */
    ADCON1 = 0x80;
 }

/***********************************************************************
*
*     FUNCTION
*
*         ADC_Init
*
*     DESCRIPTION
*
*         This function initializes the ADC.         
*
*     INPUTS
*
*         channel - ADC channel number
*
*     OUTPUTS
*
*         10-bit converted data
*
***********************************************************************/
unsigned int ADC_StartConversion(unsigned char channel)
 {
    /* Select particular channel and turn ON ADC. */
    ADCON0 = ((1 << ADON) | (channel << 3));
    __delay_us(50);
 
    /* Start ADC conversion. */
    GO = 1;
    
    /* Wait for the conversion to complete. */
    while (GO == 1);
 
    /* return right justified 10-bit result. */
    return ( (ADRESH << 8) + ADRESL );
}
