// 2.3. Реализовать очереди указателей длинных сообщений.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <string.h>    // Для использования strcpy
#include <queue.h>     // Для работы с очередями

typedef struct {
    char message[100];
} LongMessage_t;

QueueHandle_t xQueueLongMessages;

void vQueueLongMessagesTask23(void *pvParameters)
{
    LongMessage_t msgToSend;
    while(1)
    {
        strcpy(msgToSend.message, "Long message example");
        xQueueSend(xQueueLongMessages, &msgToSend, portMAX_DELAY); // Отправка сообщения в очередь
        vTaskDelay(pdMS_TO_TICKS(1000));  // Задержка 1 секунда
    }
}

void vQueueLongMessagesReceiveTask23(void *pvParameters)
{
    LongMessage_t receivedMsg;
    while(1)
    {
        if (xQueueReceive(xQueueLongMessages, &receivedMsg, portMAX_DELAY) == pdPASS) {
            printf("Received: %s\n", receivedMsg.message);
        }
    }
}

int task23(void)
{
    // Создаем очередь для длинных сообщений
    xQueueLongMessages = xQueueCreate(10, sizeof(LongMessage_t)); 

    if (xQueueLongMessages != NULL) {
        // Создаем задачи для отправки и получения сообщений
        xTaskCreate(vQueueLongMessagesTask23, "SendLongMessageTask", 100, NULL, 1, NULL);
        xTaskCreate(vQueueLongMessagesReceiveTask23, "ReceiveLongMessageTask", 100, NULL, 1, NULL);

        // Запуск планировщика
        vTaskStartScheduler();
    } else {
        printf("Queue creation failed!\n");
    }

    return 0;
}
