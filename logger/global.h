/* 
 * File:   global.h
 * Author: mirfan
 *
 * Created on February 15, 2017, 10:44 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "hal.h"

#define _USER_TIMER_FUNC                            true
    
#if (defined(_USER_TIMER_FUNC) && (_USER_TIMER_FUNC == true))
void user_timer_callback(void);
#endif

/* This define must be to use any of the built-in functions to be used. */
#define _XTAL_FREQ                                  4000000

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

