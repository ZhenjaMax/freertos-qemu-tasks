#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>

#define QUEUE_LENGTH 5
#define ITEM_SIZE sizeof(int)

QueueHandle_t xQueue;

void vQueueSendTask21(void *pvParameters)
{
    int itemToSend = 0;
    while(1)
    {
        itemToSend++;
        char buf[100];
        if (xQueueSend(xQueue, &itemToSend, pdMS_TO_TICKS(1000)) != pdPASS) {
            sprintf(buf, "Failed to send item.\n");
            vSendString(buf);  // Отправляем сообщение в консоль
        } else {
            sprintf(buf, "Sent item: %d\n", itemToSend);
            vSendString(buf);  // Отправляем сообщение в консоль
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vQueueReceiveTask21(void *pvParameters)
{
    int receivedItem;
    while(1)
    {
        char buf[100];
        if (xQueueReceive(xQueue, &receivedItem, pdMS_TO_TICKS(1000)) == pdPASS) {
            sprintf(buf, "Received item: %d.\n", receivedItem);
            vSendString(buf);  // Отправляем сообщение в консоль
        } else {
            sprintf(buf, "No item received within timeout.\n");
            vSendString(buf);  // Отправляем сообщение в консоль
        }
    }
}

int task21(void)
{
    // Создаем очередь
    xQueue = xQueueCreate(QUEUE_LENGTH, ITEM_SIZE);

    if (xQueue == NULL) {
        char buf[100];
        sprintf(buf, "Failed to create queue!\n");
        vSendString(buf);  // Отправляем сообщение в консоль
        return -1;
    }

    // Создаем задачи
    xTaskCreate(vQueueSendTask21, "SendTask", 100, NULL, 1, NULL);
    xTaskCreate(vQueueReceiveTask21, "ReceiveTask", 100, NULL, 1, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
