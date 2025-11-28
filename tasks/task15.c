// 1.5. Получить информацию о состоянии задач.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "riscv-virt.h"

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)
#define DELAY_MS         1000
#define NUM_TASKS        5

// Массив дескрипторов задач
TaskHandle_t xTaskHandles15[NUM_TASKS];

// Функция для получения состояния задачи
const char* getTaskState(TaskHandle_t xTaskHandle)
{
    switch (eTaskGetState(xTaskHandle)) {
        case eReady:
            return "Ready";
        case eBlocked:
            return "Blocked";
        case eSuspended:
            return "Suspended";
        case eDeleted:
            return "Deleted";
        case eRunning:
            return "Running";
        default:
            return "Unknown";
    }
}

// Функция задачи
void vTaskFunction15(void *pvParameters)
{
    int taskNumber = (int)pvParameters;  // Получаем номер задачи

    while(1)
    {
        // Получаем состояние текущей задачи
        const char* taskState = getTaskState(xTaskHandles15[taskNumber]);

        // Получаем текущее время (в тиках, затем в мс)
        TickType_t xTimeNow = xTaskGetTickCount();
        unsigned long ulMilliseconds = pdTICKS_TO_MS(xTimeNow);

        // Форматируем строку с информацией о состоянии задачи
        char buf[100];
        sprintf(buf, "Task %d | [%lu ms] | State: %s.", taskNumber, ulMilliseconds, taskState);
        vSendString(buf);

        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}

int task15(void)
{
    // Создание множества задач
    for (int i = 0; i < NUM_TASKS; i++) {
        // Создаем задачу с приоритетом TASK_PRIORITY и передаем номер задачи
        xTaskCreate(vTaskFunction15, "Task", TASK_STACK_SIZE, (void *)i, TASK_PRIORITY, &xTaskHandles15[i]);
    }

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
