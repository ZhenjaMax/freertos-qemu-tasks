// 4.3. Осуществить событийное планирование конкурирующих задач, провести эксперименты с разными и одинаковыми приоритетами, проанализировать очередность выполнения задач.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)

TaskHandle_t xTaskHandle431;
TaskHandle_t xTaskHandle432;

// Задача 1: Отправляет уведомление
void vTask431(void *pvParameters)
{
    while(1)
    {
        printf("Task 1 Running...\n");
        xTaskNotifyGive(xTaskHandle432); // Отправка уведомления задаче 2
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Задача 2: Принимает уведомление
void vTask432(void *pvParameters)
{
    while(1)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == pdTRUE) {
            printf("Notification received by Task 2\n");
        }
    }
}

int task43(void)
{
    // Создание задач
    xTaskCreate(vTask431, "Task431", TASK_STACK_SIZE, NULL, TASK_PRIORITY, &xTaskHandle431);
    xTaskCreate(vTask432, "Task432", TASK_STACK_SIZE, NULL, TASK_PRIORITY, &xTaskHandle432);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
