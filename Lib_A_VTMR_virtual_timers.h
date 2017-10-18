/* 
 * File:   Lib_A_vtmr_virtual_timers.h
 * Author: m.isaev
 *
 * Created on 4 октября 2017 г., 9:33
 */

#ifndef LIB_A_VTMR_VIRTUAL_TIMERS_H
#define	LIB_A_VTMR_VIRTUAL_TIMERS_H

//******************************************************************************
// Секция include (подключаем заголовочные файлы используемых модулей)
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
//******************************************************************************


//******************************************************************************
// Секция определения констант
//******************************************************************************


//******************************************************************************
// Секция определения типов

typedef enum {
    STOP,
    RUNNING,
    PAUSE,
} VTMR_tmr_state_e;

typedef struct {
    volatile uint32_t cnt;
    VTMR_tmr_state_e state;
} VTMR_tmr_s;
//******************************************************************************


//******************************************************************************
// Секция определения глобальных переменных
//******************************************************************************


//******************************************************************************
// Секция прототипов глобальных функций
extern void VTMR_StartVirtTimer(VTMR_tmr_s *vTMR);
extern void VTMR_StopVirtTimer(VTMR_tmr_s *vTMR);
extern void VTMR_PauseVirtTimer(VTMR_tmr_s *vTMR);
extern void VTMR_ResetVirtTimer(VTMR_tmr_s *vTMR);
extern void VTMR_IntProcess(VTMR_tmr_s *vTMR);
//******************************************************************************


//******************************************************************************
// Секция определения макросов
//******************************************************************************

#endif	/* LIB_A_VTMR_VIRTUAL_TIMERS_H */

////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////


