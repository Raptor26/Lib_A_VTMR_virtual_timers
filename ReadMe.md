## Changelog

### Пример использования библиотеки виртуальных таймеров с инкрементом счетчика в прерывании от аппаратного таймера ###

```C
// Подключение библиотеки виртуальных таймеров
#include "Lib_A_VTMR_virtual_timers.h"

// Объявление глобальных переменных структур виртуальных таймеров
VTMR_tmr_s  myVirtTimer1CntStruct,
            myVirtTimer2CntStruct;
// Объявление глобальных переменных для записи временных интервалов
uint32_t    myVirtTimer1Value,
            myVirtTimer2Value;
 
int main(void)
{
    ...
    // Разрешает инкремент виртуального таймера при вызове
    // функции VTMR_IntProcess();
    VTMR_StartVirtTimer(&myVirtTimer1CntStruct);
    VTMR_StartVirtTimer(&myVirtTimer2CntStruct);
    ...
    while(1)
    {
        ...
        // Разрешает инкремент виртуального таймера при вызове
        // функции VTMR_IntProcess() и сбрасывает значение
        // счетчика в нуль - перезапуск виртуального таймера;
        VTMR_RestartVirtTimer(&myVirtTimer1CntStruct);
        VTMR_RestartVirtTimer(&myVirtTimer2CntStruct);
        ...
        // Получение количества вызова функции VTMR_IntProcess();
        // (получение количества прерываний  "void TIMER_1_INTERRUPT(void)")
         myVirtTimer1Value = 
            VTMR_GetValueVirtTimer(&myVirtTimer1CntStruct);
         myVirtTimer2Value = 
            VTMR_GetValueVirtTimer(&myVirtTimer2CntStruct);
 
        // Причем
        myVirtTimer1Value == myVirtTimer1CntStruct.timeInterval;
        myVirtTimer2Value == myVirtTimer2CntStruct.timeInterval;
 
        // Запрещает инкремент виртуального таймера при вызове
        // функции VTMR_IntProcess() - остановка виртуального таймера;
        VTMR_StopVirtTimer(&myVirtTimer1CntStruct);
        VTMR_StopVirtTimer(&myVirtTimer2CntStruct);
    }
}
 
void TIMER_1_INTERRUPT(void)
{
    ...
    VTMR_IntProcess(&myVirtTimer1CntStruct);
    VTMR_IntProcess(&myVirtTimer2CntStruct);
    ...
}
```

### Пример использования библиотеки виртуальных таймеров с инкрементом счетчика напрямую от аппаратного таймера/таймеров без использования прерываний ###

```C
// Подключение библиотеки виртуальных таймеров
#include "Lib_A_VTMR_virtual_timers.h"

// Объявление глобальных переменных структур виртуальных таймеров
VTMR_tmr_s  myVirtTimer1CntStruct,
            myVirtTimer2CntStruct;
// Объявление глобальных переменных для записи временных интервалов
uint32_t    myVirtTimer1Value,
            myVirtTimer2Value;
 
int main(void)
{
    ...
    // Пример инициализации для микроконтроллеров PIC:
    // где TMR9 - указатель на старшие 16 бит аппаратного счетчика;
    //     TMR8 - указатель на младшие 16 бит аппаратного счетчика;
    VTMR_InitTimerStruct(
        &myVirtTimer1CntStruct,
        (uint16_t*) &TMR9,
        (uint16_t*) &TMR8);
    VTMR_InitTimerStruct(
        &myVirtTimer2CntStruct,
        (uint16_t*) &TMR9,
        (uint16_t*) &TMR8);
 
    // Пример инициализации для микроконтроллеров STM32;
    // где TIM3->CNT - указатель на старшие 16 бит аппаратного счетчика;
    //     TIM4->CNT - указатель на младшие 16 бит аппаратного счетчика;
    VTMR_InitTimerStruct(
        &myVirtTimer1CntStruct,
        (uint16_t*) &TIM3->CNT,
        (uint16_t*) &TIM4->CNT);
    VTMR_InitTimerStruct(
        &myVirtTimer2CntStruct,
        (uint16_t*) &TIM3->CNT,
        (uint16_t*) &TIM4->CNT);
 
    // Если используется только 16 битный таймер вместо 32 битного, то
    // в качестве указателя на старшие 16 бит аппаратного счетчика
    // следует передать NULL
    VTMR_InitTimerStruct(
        &myVirtTimer1CntStruct,
        (uint16_t*) NULL,
        (uint16_t*) &TIM4->CNT);
    VTMR_InitTimerStruct(
        &myVirtTimer2CntStruct,
        (uint16_t*) NULL,
        (uint16_t*) &TIM4->CNT);
    ...
    while(1)
    {
        ...
        // Запись в переменную счетчика текущего значения
        // аппаратного счетчика;
        // @see VTMR_tmr_s;
        VTMR_StartTimer(&myVirtTimer1CntStruct);
        VTMR_StartTimer(&myVirtTimer2CntStruct);
        ...
 
        // Определение разницы между текущим значением аппаратного
        // счетчика и значением переменной счетчика в
        // структуре myVirtTimer1CntStruct.
        // В результате имеем количество тиков аппаратного счетчика
        // между вызовами функций VTMR_StartTimer() и VTMR_GetTimerValue();
        // @see VTMR_tmr_s;
        myVirtTimer1Value = 
            VTMR_GetTimerValue(
                &myVirtTimer1CntStruct);
        myVirtTimer2Value = 
            VTMR_GetTimerValue(
                &myVirtTimer2CntStruct);
 
        // Причем
        myVirtTimer1Value == myVirtTimer1CntStruct.timeInterval;
        myVirtTimer2Value == myVirtTimer2CntStruct.timeInterval;
        ...
    }
}
```