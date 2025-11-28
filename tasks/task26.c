// 2.6. Привести пример использования счетного семафора для подсчета событий.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <semphr.h>

SemaphoreHandle_t xSemaphore;

void vEventCountingTask26(void *pvParameters)
{
    while(1)
    {
        // Ожидаем события
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            printf("Event occurred\n");
        }
    }
}

int task26(void)
{
    // Создаем счетный семафор, который может иметь максимум 10 событий, начинаем с 0
    xSemaphore = xSemaphoreCreateCounting(10, 0);

    if (xSemaphore != NULL) {
        // Создаем задачу
        xTaskCreate(vEventCountingTask26, "EventCountingTask", 100, NULL, 1, NULL);

        // Симуляция события (увеличиваем счетчик семафора)
        xSemaphoreGive(xSemaphore);

        // Запуск планировщика
        vTaskStartScheduler();
    } else {
        printf("Failed to create counting semaphore!\n");
    }

    return 0;
}
