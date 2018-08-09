/**
 * @file    "Lib_A_VTMR_virtual_timers.h"
 * @author  Isaev Mickle;
 * @version 1.2
 * @date    09.08.2018
 */

#ifndef LIB_A_VTMR_VIRTUAL_TIMERS_H
#define	LIB_A_VTMR_VIRTUAL_TIMERS_H

//******************************************************************************
// Секция include (подключаем заголовочные файлы используемых модулей)
#include <stdint.h>
#include <stddef.h>
//******************************************************************************


//******************************************************************************
// Секция определения констант
#define VTMR_16BIT_CNT_MAX_VAL				((uint16_t)0xFFFF)
#define VTMR_32BIT_CNT_MAX_VAL				((uint32_t)0xFFFFFFFF)
//******************************************************************************


//******************************************************************************
// Секция определения типов

typedef enum {
    VTMR_STOP,
    VTMR_RUNNING,
} VTMR_tmr_status_e;

typedef struct {
    /**
     * @brief   Переменная для записи текущего значения аппаратного счетчика;
     */
     uint32_t volatile cnt;

    /**
     * @brief   Указатель на старшие 16 бит аппаратного счетчика;
     */
    const uint16_t volatile const *pHighCntReg;

    /**
     * @brief   Указатель на младшие 16 бит аппаратного счетчика;
     */
    const uint16_t volatile const *pLowCntReg;

    /**
     * @brief   В данную переменную записывается временной интервал между
     *          вызовами функции "VTMR_StartTimer" и "VTMR_GetValueTimer" в тиках
     *          аппаратного счетчика;
     */
    uint32_t timeInterval;

    uint32_t timeIntervalMax;
    
    /**
     * @brief   Текущее состояние виртуального таймера;
     * @note    Запущен или остановлен;
     */
     VTMR_tmr_status_e volatile state;
} VTMR_tmr_s;
//******************************************************************************


//******************************************************************************
// Секция определения глобальных переменных
//******************************************************************************


//******************************************************************************
// Секция прототипов глобальных функций
/* ######################################################################### */
/* <Функции виртуальных таймеров, инкремент которых происходит в прерывании> */
/* ######################################################################### */
extern void 
VTMR_RestartVirtTimer(
        VTMR_tmr_s *vTMR);

extern void
VTMR_StopVirtTimer(
        VTMR_tmr_s *vTMR);

extern void
VTMR_StartVirtTimer(
        VTMR_tmr_s *vTMR);

extern uint32_t
VTMR_GetValueVirtTimer(
        VTMR_tmr_s *vTMR);

extern void
VTMR_IntProcess(
        VTMR_tmr_s *vTMR);

/* ################################################################## */
/* <Функции виртуальных таймеров, привязанных к аппаратному счетчику> */
/* ################################################################## */
extern void
VTMR_StartTimer(
        VTMR_tmr_s *pVTMR);

extern uint32_t
VTMR_GetTimerValue(
        VTMR_tmr_s *pVTMR);

extern uint32_t
VTMR_GetMaxTimerValue(
        VTMR_tmr_s *pVTMR);

extern void
VTMR_InitTimerStruct(
        VTMR_tmr_s *pVTMR,
        const uint16_t * const pHighCntReg,
        const uint16_t * const pLowCntReg);
//******************************************************************************


//******************************************************************************
// Секция определения макросов
//******************************************************************************

#endif	/* LIB_A_VTMR_VIRTUAL_TIMERS_H */

////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
