// 5.4. Организовать отправку/прием уведомлений из/в обработчик разными способами (включая допустимые IPC).

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)

// Хендлы задач
TaskHandle_t xTaskHandle541;
TaskHandle_t xTaskHandle542;

// Переменная для хранения уведомлений
volatile uint32_t notificationValue = 0;

// interrupt_handler объявлен в main.c

// Задача 1: Получает уведомление
void vTask541(void *pvParameters)
{
    while(1)
    {
        // Ожидаем уведомления
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == pdTRUE) {
            printf("Notification received by Task1\n");
        }
    }
}

// Задача 2: Отправляет уведомление
void vTask542(void *pvParameters)
{
    while(1)
    {
        // Отправка уведомления задаче 1
        xTaskNotifyGive(xTaskHandle541);
        printf("Notification sent by Task2\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int task54(void)
{
    // Создание задач
    xTaskCreate(vTask541, "Task541", TASK_STACK_SIZE, NULL, TASK_PRIORITY, &xTaskHandle541);
    xTaskCreate(vTask542, "Task542", TASK_STACK_SIZE, NULL, TASK_PRIORITY, &xTaskHandle542);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
