// 3.2. Использовать уведомления в качестве более эффективного легкого средства, чем отдельные объекты IPC, такие как двоичные и счетные семафоры (программы п.2.5, 2.6), группа событий и почтовый ящик.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)

TaskHandle_t xTask32Handle;

void vNotifyTask32(void *pvParameters)
{
    while(1)
    {
        // Задержка перед отправкой уведомления
        vTaskDelay(pdMS_TO_TICKS(1000));
        // Отправка уведомления задаче
        xTaskNotifyGive(xTask32Handle);
    }
}

void vTaskWaitForNotification32(void *pvParameters)
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

int task32(void)
{
    // Создаем задачу для ожидания уведомлений
    xTaskCreate(vTaskWaitForNotification32, "WaitForNotify", TASK_STACK_SIZE, NULL, TASK_PRIORITY, &xTask32Handle);

    // Создаем задачу для отправки уведомлений
    xTaskCreate(vNotifyTask32, "NotifyTask", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
