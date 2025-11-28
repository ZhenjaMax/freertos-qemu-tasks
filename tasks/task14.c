// 1.4. Создать конкурирующий поток – задачу, создать множество задач.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "riscv-virt.h"

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)
#define DELAY_MS         1000
#define NUM_TASKS        5

// Массив дескрипторов задач
TaskHandle_t xTaskHandles14[NUM_TASKS];

// Функция задачи
void vTaskFunction14(void *pvParameters)
{
    int taskNumber = (int)pvParameters;  // Получаем номер задачи

    while(1)
    {
        // Получаем приоритет текущей задачи
        UBaseType_t uxPriority = uxTaskPriorityGet(NULL);

        // Получаем текущее время (в тиках, затем в мс)
        TickType_t xTimeNow = xTaskGetTickCount();
        unsigned long ulMilliseconds = pdTICKS_TO_MS(xTimeNow);

        char buf[100];
        sprintf(buf, "Task %d | [%lu ms] | Priority: %lu | Task is running...", taskNumber, ulMilliseconds, uxPriority);
        vSendString(buf);

        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}

int task14(void)
{
    // Создание множества задач
    for (int i = 0; i < NUM_TASKS; i++) {
        // Создаем задачу с приоритетом TASK_PRIORITY и передаем номер задачи
        xTaskCreate(vTaskFunction14, "Task", TASK_STACK_SIZE, (void *)i, TASK_PRIORITY, &xTaskHandles14[i]);
    }

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
