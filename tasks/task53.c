// 5.3. Замаскировать прерывания одного устройства и затем восстановить (можно на примере клавиатуры или монитора).

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)

void vTask53(void *pvParameters)
{
    while(1)
    {
        // MaskInterrupt(DEVICE_KEYBOARD);

        printf("Interrupts for keyboard masked\n");

        vTaskDelay(pdMS_TO_TICKS(2000)); // Пауза для имитации работы

        // Восстанавливаем прерывание устройства
        // UnmaskInterrupt(DEVICE_KEYBOARD);
        
        printf("Interrupts for keyboard unmasked\n");

        vTaskDelay(pdMS_TO_TICKS(2000)); // Пауза
    }
}

int task53(void)
{
    // Создание задачи
    xTaskCreate(vTask53, "Task53", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
