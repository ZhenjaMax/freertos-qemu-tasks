// 2.5. Реализовать очередь с одним элементом как бинарный семафор (в дальнейшем использовать этот прием для синхронизации задачи и ISR периф. устройства).

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <semphr.h>

SemaphoreHandle_t xBinarySemaphore;

void vBinarySemaphoreTask25(void *pvParameters)
{
    while(1)
    {
        // Ожидаем семафор
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE) {
            printf("Semaphore received\n");
        }
    }
}

int task25(void)
{
    // Создаем бинарный семафор
    xBinarySemaphore = xSemaphoreCreateBinary();

    if (xBinarySemaphore != NULL) {
        // Создаем задачу
        xTaskCreate(vBinarySemaphoreTask25, "BinarySemaphoreTask", 100, NULL, 1, NULL);

        // Устанавливаем семафор
        xSemaphoreGive(xBinarySemaphore);  // Освобождаем семафор

        // Запуск планировщика
        vTaskStartScheduler();
    } else {
        printf("Failed to create binary semaphore!\n");
    }

    return 0;
}
