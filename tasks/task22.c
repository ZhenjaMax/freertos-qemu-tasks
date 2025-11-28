// 2.2. Использовать наборы очередей.

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>

#define NUM_QUEUES 3
QueueHandle_t xQueueSet;

void vQueueSetTask22(void *pvParameters)
{
    int itemToSend = 0;
    while(1)
    {
        itemToSend++;
        xQueueSendToBack(xQueueSet, &itemToSend, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int task22(void)
{
    xQueueSet = xQueueCreate(NUM_QUEUES, sizeof(int));

    xTaskCreate(vQueueSetTask22, "QueueSetTask", 100, NULL, 1, NULL);

    vTaskStartScheduler();

    return 0;
}
