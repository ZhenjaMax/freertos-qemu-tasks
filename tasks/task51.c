#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)

void vTask51(void *pvParameters)
{
    while(1)
    {
        // Запрещаем все прерывания
        taskENTER_CRITICAL();
        char buf[100];
        sprintf(buf, "Interrupts disabled\n");
        vSendString(buf);  // Отправляем сообщение в консоль

        vTaskDelay(pdMS_TO_TICKS(1000)); // Пауза

        // Разрешаем все прерывания
        taskEXIT_CRITICAL();
        sprintf(buf, "Interrupts enabled\n");
        vSendString(buf);  // Отправляем сообщение в консоль

        vTaskDelay(pdMS_TO_TICKS(1000)); // Пауза
    }
}

int task51(void)
{
    // Создание задачи
    xTaskCreate(vTask51, "Task51", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
