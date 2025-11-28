// 4.2. Установить квант времени исполнения. Применить функции освобождения ЦП (усыпить поток, перевести в конец очереди готовых).

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

// Задача для демонстрации квантования времени
void vTaskWithTimeSlice(void *pvParameters)
{
    while(1)
    {
        printf("Task with Time Slice Running...\n");
        vTaskDelay(pdMS_TO_TICKS(500));  // Задержка, которая демонстрирует работу с квантованием времени
    }
}

int task42(void)
{
    // Создание задачи с квантованием времени
    xTaskCreate(vTaskWithTimeSlice, "TimeSliceTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
