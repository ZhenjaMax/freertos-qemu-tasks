// 4.5. Установить планирование с истечением крайнего срока, представить эксперимент, доказывающий исполнение этой политики.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#define TASK_PERIOD pdMS_TO_TICKS(1000) // Период задачи

// Задача с крайнем сроком
void vTaskWithDeadline(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
        printf("Task with Deadline Running...\n");
        vTaskDelayUntil(&xLastWakeTime, TASK_PERIOD);
    }
}

int task45(void)
{
    // Создание задачи с установленным периодом
    xTaskCreate(vTaskWithDeadline, "TaskWithDeadline", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
