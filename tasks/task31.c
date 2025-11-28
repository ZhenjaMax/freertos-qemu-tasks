// 3.1. Сгенерировать событие прямого уведомления (разными способами).

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)

TaskHandle_t xTask31Handle;

void vNotifyTask31(void *pvParameters)
{
    while(1)
    {
        // Задержка перед отправкой уведомления
        vTaskDelay(pdMS_TO_TICKS(1000));
        // Отправка уведомления задаче
        xTaskNotifyGive(xTask31Handle);
    }
}

void vTaskWaitForNotification31(void *pvParameters)
{
    uint32_t ulNotificationValue;

    while(1)
    {
        // Ожидание уведомления
        ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        if (ulNotificationValue > 0) {
            // Изменение формата вывода для uint32_t
            printf("Notification received by task: %lu\n", ulNotificationValue);
        }
    }
}

int task31(void)
{
    // Создаем задачу для ожидания уведомлений
    xTaskCreate(vTaskWaitForNotification31, "WaitForNotify", TASK_STACK_SIZE, NULL, TASK_PRIORITY, &xTask31Handle);

    // Создаем задачу для отправки уведомлений
    xTaskCreate(vNotifyTask31, "NotifyTask", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
