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
//******************************************************************************


//******************************************************************************
// Секция определения констант
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
    volatile uint32_t cnt;

    /**
     * @brief   Указатель на старшие 16 бит аппаратного счетчика;
     */
    uint32_t *pHighCntReg;

    /**
     * @brief   Указатель на младшие 16 бит аппаратного счетчика;
     */
    uint32_t *pLowCntReg;

    /**
     * @brief   В данную переменную записывается временной интервал между
     *          вызовами функции "VTMR_StartTimer" и "VTMR_GetValueTimer" в тиках
     *          аппаратного счетчика;
     */
    uint32_t timeInterval;

    /**
     * @brief   Текущее состояние виртуального таймера;
     * @note    Запущен или остановлен;
     */
    VTMR_tmr_status_e state;
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
extern void VTMR_RestartVirtTimer(
        VTMR_tmr_s *vTMR);

extern void VTMR_StopVirtTimer(
        VTMR_tmr_s *vTMR);

extern void VTMR_StartVirtTimer(
        VTMR_tmr_s *vTMR);

extern uint32_t VTMR_GetValueVirtTimer(
        VTMR_tmr_s *vTMR);

extern void VTMR_IntProcess(
        VTMR_tmr_s *vTMR);

/* ################################################################## */
/* <Функции виртуальных таймеров, привязанных к аппаратному счетчику> */
/* ################################################################## */
extern void VTMR_StartTimer(
        VTMR_tmr_s *pVTMR);

extern uint32_t VTMR_GetTimerValue(
        VTMR_tmr_s *pVTMR);

extern uint32_t VTMR_GetMaxTimerValue(
        VTMR_tmr_s *pVTMR);

void VTMR_InitTimerStruct(
        VTMR_tmr_s *pVTMR,
        uint32_t *pHighCntReg,
        uint32_t *pLowCntReg);
//******************************************************************************


//******************************************************************************
// Секция определения макросов
//******************************************************************************

#endif	/* LIB_A_VTMR_VIRTUAL_TIMERS_H */

////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
