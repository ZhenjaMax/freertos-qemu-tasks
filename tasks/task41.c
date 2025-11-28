// 4.1. Исследовать планирование по умолчанию (single-core), изменяя последовательно параметры configUSE_PREEMPTION и configUSE_TIME_SLICING (см. в установочном файле FreeRTOSConfig.h), привести примеры исполнения и конкурирования.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

// Задача с более высоким приоритетом
void vTaskHighPriority(void *pvParameters)
{
    while(1)
    {
        printf("High Priority Task Running...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Задача с более низким приоритетом
void vTaskLowPriority(void *pvParameters)
{
    while(1)
    {
        printf("Low Priority Task Running...\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

int task41(void)
{
    // Создание двух задач с разными приоритетами
    xTaskCreate(vTaskHighPriority, "HighPriority", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vTaskLowPriority, "LowPriority", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
