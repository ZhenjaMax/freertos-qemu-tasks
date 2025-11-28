#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "FreeRTOSConfig.h"
#include "riscv-virt.h" // Включение специфичных заголовочных файлов для вашей платформы

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)
#define INTERRUPT_NUMBER 3 // Пример прерывания (обновите по необходимости)

TaskHandle_t xTaskHandle52 = NULL; // Дескриптор задачи

// Обработчик прерывания
void interrupt_handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Уведомление задачи о прерывании
    xTaskNotifyFromISR(xTaskHandle52, 0, eNoAction, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// Пример функции для регистрации обработчика прерывания для RISC-V
void register_interrupt_handler(uint32_t interrupt_number, void (*handler)(void))
{
    // Настройка прерывания для конкретного контроллера прерываний RISC-V (например, PLIC)
    // Пример: Настроить прерывание на определенном уровне (int_number) и зарегистрировать обработчик
    // Для упрощения этот код требует реализации специфической для вашего контроллера прерываний
    // Например:
    // PLIC_set_interrupt_handler(interrupt_number, handler);
    // PLIC_enable_interrupt(interrupt_number);
    // Важно, чтобы этот код был совместим с конкретной реализацией вашего контроллера прерываний.
}

void vTask52(void *pvParameters)
{
    // Запоминаем дескриптор текущей задачи
    xTaskHandle52 = xTaskGetCurrentTaskHandle();

    while(1)
    {
        // Ожидание уведомления от обработчика прерывания
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Логика задачи, которая выполняется после прерывания
        printf("Interrupt handled and task resumed...\n");

        vTaskDelay(pdMS_TO_TICKS(1000)); // Пауза
    }
}

int task52(void)
{
    // Создание задачи
    xTaskCreate(vTask52, "Task52", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Регистрация обработчика прерывания
    register_interrupt_handler(INTERRUPT_NUMBER, interrupt_handler);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
