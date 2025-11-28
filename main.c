#include <stdio.h>
#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include "trcRecorder.h"

#define mainVECTOR_MODE_DIRECT 1
#define STOP_TIME_FRAC_MS 100
#define STOP_TIME_MS 5000

extern void freertos_risc_v_trap_handler( void );
extern void freertos_vector_table( void );

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask,
                                    char * pcTaskName );
void vApplicationTickHook( void );

// void interrupt_handler(void) 
// {
//     printf("Interrupt triggered\n");
// }
// void interrupt_handler(void)
// {
//     // Пример отправки уведомления из обработчика
//     BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//     vTaskNotifyGiveFromISR(xTaskHandle541, &xHigherPriorityTaskWoken);
//     printf("Notification sent from interrupt handler\n");

//     // Если задача 1 была заблокирована, в случае высокого приоритета она будет разблокирована
//     portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
// }

extern int task(void);

int main( void )
{
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
    vTaskStartScheduler();

    vTraceStop();  // Останавливаем трассировку
    vTraceFlush("trace_output.tztrace");  // Сохраняем данные трассировки

    return 0;
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    taskDISABLE_INTERRUPTS();

    for( ; ; )
    {
    }
}

void vApplicationIdleHook( void ){}

void vApplicationStackOverflowHook( TaskHandle_t pxTask,
                                    char * pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    taskDISABLE_INTERRUPTS();

    for( ; ; ) {}
}

void vApplicationTickHook( void ) {}
/*-----------------------------------------------------------*/

void vAssertCalled( void )
{
    volatile uint32_t ulSetTo1ToExitFunction = 0;

    taskDISABLE_INTERRUPTS();

    while( ulSetTo1ToExitFunction != 1 )
    {
        __asm volatile ( "NOP" );
    }
}
