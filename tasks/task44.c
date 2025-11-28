// 4.4. Заблокировать планировщик, проанализировать результат, разблокировать.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

// Задача
void vTask441(void *pvParameters)
{
    while(1)
    {
        printf("Task 1 Running...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int task44(void)
{
    // Заблокировать планировщик
    vTaskSuspendAll();

    // Создание задачи
    xTaskCreate(vTask441, "Task441", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    // Разблокировать планировщик
    xTaskResumeAll();

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
