// 2.8. Привести практический пример применения рекурсивного мьютекса.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <semphr.h>

SemaphoreHandle_t xRecursiveMutex;

void vRecursiveMutexTask28(void *pvParameters)
{
    while(1)
    {
        // Захват рекурсивного мьютекса
        if (xSemaphoreTakeRecursive(xRecursiveMutex, portMAX_DELAY) == pdTRUE) {
            printf("Accessing critical section 1\n");

            // Второй захват рекурсивного мьютекса
            if (xSemaphoreTakeRecursive(xRecursiveMutex, portMAX_DELAY) == pdTRUE) {
                printf("Accessing critical section 2\n");
                xSemaphoreGiveRecursive(xRecursiveMutex);  // Освобождаем второй раз
            }

            xSemaphoreGiveRecursive(xRecursiveMutex);  // Освобождаем первый раз
        }
    }
}

int task28(void)
{
    // Создаем рекурсивный мьютекс
    xRecursiveMutex = xSemaphoreCreateRecursiveMutex();

    if (xRecursiveMutex != NULL) {
        // Создаем задачу, которая будет работать с рекурсивным мьютексом
        xTaskCreate(vRecursiveMutexTask28, "RecursiveMutexTask", 100, NULL, 1, NULL);

        // Запуск планировщика
        vTaskStartScheduler();
    } else {
        printf("Failed to create recursive mutex!\n");
    }

    return 0;
}
