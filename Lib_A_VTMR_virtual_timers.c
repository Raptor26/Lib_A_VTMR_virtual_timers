/**
 * @file   	Lib_A_VTMR_virtual_timers.c
 * @author 	Mickle Isaev
 * @version
 * @date 	18-фев-2019
 * @brief	Библиотека содержит API для работы с виртуальными таймерами
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "Lib_A_VTMR_virtual_timers.h"
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/


/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      18-фев-2019
 *
 * @brief    Функция выполняет сброс полей структуры инициализации в NULL
 *
 * @param[in]    pVirtTMRInit    Указатель на инициализирующую структуру
 *                               виртуальных таймеров
 *
 * @return    None
 */
void
VTMR_StructInit(
	vtrm_tmr_init_s *pVirtTMRInit)
{
	pVirtTMRInit->pHighCntReg 	= NULL;
	pVirtTMRInit->pLowCntReg 	= NULL;
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      18-фев-2019
 *
 * @brief 	Функция инициализирует структуру виртуального таймера
 *
 * @note  	Если поле "pVirtTMRInit->pHighCntReg == NULL", то таймер
 *          работает в 16-ти битном режиме
 *
 * @param[out]	*pVirtTMR:       Указатель на структуру виртуального таймера
 * @param[in] 	*pVirtTMRInit:   Указатель на инициализирующую структуру
 *                               виртуальных таймеров
 *
 * @return    None
 */
void
VTMR_Init(
	vtrm_tmr_s 		*pVirtTMR,
	vtrm_tmr_init_s *pVirtTMRInit)
{
	pVirtTMR->pHighCntReg 		= pVirtTMRInit->pHighCntReg;
	pVirtTMR->pLowCntReg 		= pVirtTMRInit->pLowCntReg;
	pVirtTMR->cnt 				= 0u;
	pVirtTMR->timeInterval 		= 0u;
	pVirtTMR->timeIntervalMax 	= 0u;
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      18-фев-2019
 *
 * @brief    Функция "Запускает" таймер
 *
 * @details  Функция записывает в поле структуры текущее значение
 * 			 аппаратного счетчика
 *
 * @param[out]	*pVirtTMR: 	Указатель на структуру виртуального таймера
 *
 * @return    None
 */
void
VTMR_StartTimer(
	vtrm_tmr_s *pVTMR)
{
	/* Если режим работы таймера 32-х битный */
	if (pVTMR->pHighCntReg != NULL)
	{
		uint32_t highCnt 	= (uint32_t) (*pVTMR->pHighCntReg);
		uint32_t lowCnt 	= (uint32_t) (*pVTMR->pLowCntReg);

		pVTMR->cnt =
			(((highCnt << 16) & 0xFFFF0000)
			 | (lowCnt & 0x0000FFFF));
	}
	/* Иначе, если режим работы таймера 16-ти битный */
	else
	{
		pVTMR->cnt = (uint32_t) (*pVTMR->pLowCntReg);
	}
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      18-фев-2019
 *
 * @brief    Функция "Останавливает" таймер
 *
 * @details  Функция записывает текущее значение аппаратного таймера и
 *           вычитает это значение из значения, полученного при вызове
 *           функции VTMR_StartTimer()
 *
 * @param[out]	*pVirtTMR: 	Указатель на структуру виртуального таймера
 *
 * @return    None
 */
uint32_t
VTMR_GetTimerValue(
	vtrm_tmr_s *pVTMR)
{
	/* Если режим работы таймера 32-х битный */
	if (pVTMR->pHighCntReg != NULL)
	{
		uint32_t highCnt = (uint32_t) * pVTMR->pHighCntReg,
				 lowCnt = (uint32_t) * pVTMR->pLowCntReg;

		uint32_t cnt32Bit =
			(((highCnt << 16) & 0xFFFF0000)
			 | (lowCnt & 0x0000FFFF));

		/* Если было обнуление аппаратного счетчика */
		if (pVTMR->cnt >= cnt32Bit)
		{
			pVTMR->timeInterval =
				VTMR_32BIT_CNT_MAX_VAL - pVTMR->cnt + cnt32Bit;
		}
		else
		{
			pVTMR->timeInterval =
				cnt32Bit - pVTMR->cnt;
		}
	}
	/* Иначе, если режим работы таймера 16-ти битный */
	else
	{
		/* Если было обнуление аппаратного счетчика */
		if (pVTMR->cnt >= *pVTMR->pLowCntReg)
		{
			pVTMR->timeInterval =
				(((uint32_t) ((VTMR_16BIT_CNT_MAX_VAL - (uint16_t) pVTMR->cnt) + (uint16_t) * pVTMR->pLowCntReg)) & 0x0000FFFF);
		}
		else
		{
			pVTMR->timeInterval =
				(((uint32_t) ((uint16_t) * pVTMR->pLowCntReg - (uint16_t) pVTMR->cnt)) & 0x0000FFFF);
		}
	}
	return pVTMR->timeInterval;
}
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*#### |Begin| --> Секция - "Обработчики прерываний" #########################*/
/*#### |End  | <-- Секция - "Обработчики прерываний" #########################*/

/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
