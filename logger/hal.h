/* 
 * File:   hal.h
 * Author: mirfan
 *
 * Created on February 15, 2017, 7:37 PM
 */

#ifndef HAL_H
#define	HAL_H

#ifdef	__cplusplus
extern "C" {
#endif

/* TIMER1 public routines. */
char TIMER_init(char time_period);
void TIMER_Start();

/* ADC public routines. */
void ADC_Init();
unsigned int ADC_StartConversion(unsigned char channel);

/* UART public routines. */
void UART_Init();
void UART_TxChar(char c);
void UART_TxString(const unsigned char *string);


#ifdef	__cplusplus
}
#endif

#endif	/* HAL_H */

