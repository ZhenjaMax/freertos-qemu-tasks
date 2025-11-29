// 1.2. Выяснить приоритет текущей задачи.

#include <FreeRTOS.h>
#include <task.h>
#include "riscv-virt.h"

#include <stdio.h>

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 1)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)
#define DELAY_MS 1000

void vTaskFunction(void *pvParameters)
{
    while(1)
    {
        // Получаем приоритет текущей задачи
        UBaseType_t uxPriority = uxTaskPriorityGet(NULL);

        char buf[100];
        sprintf(buf, "Task priority: %lu | Task is running...", uxPriority);
        vSendString(buf);
        
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}

int task(void)
{
    xTaskCreate(vTaskFunction, "Task", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    return 0;
}
