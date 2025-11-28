// 4.6. Продемонстрировать SMP и ASMP планирование (используя профилирование).

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

// Задача 1
void vTask461(void *pvParameters)
{
    while(1)
    {
        printf("Task 1 Running on CPU\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Задача 2
void vTask462(void *pvParameters)
{
    while(1)
    {
        printf("Task 2 Running on CPU\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int task46(void)
{
    // Создание задач для SMP или ASMP
    xTaskCreate(vTask461, "Task461", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vTask462, "Task462", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
