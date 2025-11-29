#include <FreeRTOS.h>
#include <task.h>

#include "trcRecorder.h"

#include <stdio.h>
#include <stdlib.h>
#include <timers.h>

#define mainVECTOR_MODE_DIRECT 1
#define STOP_TIME_FRAC_MS 100
#define TRACE_SAVE_DELAY_MS 4000

extern void freertos_risc_v_trap_handler(void);
extern void freertos_vector_table(void);

void vApplicationMallocFailedHook(void);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char * pcTaskName);
void vApplicationTickHook(void);

static void prvTraceSaveCallback(TimerHandle_t xTimer)
{
    (void) xTimer;
    vTraceStop();
    vTraceFlush("traces/trace_output.tztrace");
}

extern int task(void);

int main( void )
{
    TimerHandle_t xTraceSaveTimer = NULL;
    vTraceEnable(TRC_START);
    
    /* trap handler initialization */
    #if (mainVECTOR_MODE_DIRECT == 1)
    {
        __asm__ volatile ( "csrw mtvec, %0" : : "r" ( freertos_risc_v_trap_handler ) );
    }
    #else
    {
        __asm__ volatile ( "csrw mtvec, %0" : : "r" ( ( uintptr_t ) freertos_vector_table | 0x1 ) );
    }
    #endif
    
    task();

    xTraceSaveTimer = xTimerCreate("TraceSave",
        pdMS_TO_TICKS(TRACE_SAVE_DELAY_MS),
        pdFALSE,
        NULL,
        prvTraceSaveCallback
    );

    if(xTraceSaveTimer != NULL)
    {
        xTimerStart(xTraceSaveTimer, 0);
    }
    
    vTaskStartScheduler();

    return 0;
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook(void)
{
    taskDISABLE_INTERRUPTS();
    for( ; ; ){}
}

void vApplicationIdleHook(void) {}
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char * pcTaskName)
{
    (void) pcTaskName;
    (void) pxTask;
    taskDISABLE_INTERRUPTS();
    for( ; ; ) {}
}

void vApplicationTickHook(void) {}
void vAssertCalled(void)
{
    volatile uint32_t ulSetTo1ToExitFunction = 0;
    taskDISABLE_INTERRUPTS();
    while(ulSetTo1ToExitFunction != 1)
    {
        __asm volatile ("NOP");
    }
}
