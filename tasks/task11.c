// 1.1. Создать поток исполнения – задачу (task).

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "riscv-virt.h"

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 1)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)
#define DELAY_MS 1000

void vTaskFunction(void *pvParameters)
{
    while(1)
    {
        // Получаем текущее время (в тиках, затем в мс)
        TickType_t xTimeNow = xTaskGetTickCount();
        unsigned long ulMilliseconds = pdTICKS_TO_MS(xTimeNow);

        char buf[100];
        sprintf(buf, "111 %lu ms | \tTask is running...", ulMilliseconds);
        vSendString(buf);

        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}

int task(void)
{
    // Создание задачи
    xTaskCreate(vTaskFunction, "Task", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    return 0;
}
