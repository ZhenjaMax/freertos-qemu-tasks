// 2.7. Обеспечить взаимное исключение при доступе в критическую секцию средствами мьютексов.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <semphr.h>

SemaphoreHandle_t xMutex;

void vMutexTask27(void *pvParameters)
{
    while(1)
    {
        // Захват мьютекса
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
            printf("Critical section accessed\n");
            vTaskDelay(pdMS_TO_TICKS(500));  // Задержка
            // Освобождаем мьютекс
            xSemaphoreGive(xMutex);
        }
    }
}

int task27(void)
{
    // Создаем мьютекс
    xMutex = xSemaphoreCreateMutex();

    if (xMutex != NULL) {
        // Создаем задачу, которая будет работать с мьютексом
        xTaskCreate(vMutexTask27, "MutexTask", 100, NULL, 1, NULL);

        // Запуск планировщика
        vTaskStartScheduler();
    } else {
        printf("Failed to create mutex!\n");
    }

    return 0;
}
