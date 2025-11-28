// 1.3. Изменить/задать приоритет, выяснить границы приоритетов.

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "riscv-virt.h"

#define TASK_PRIORITY    (tskIDLE_PRIORITY + 2)
#define TASK_STACK_SIZE  (configMINIMAL_STACK_SIZE)
#define DELAY_MS 1000

void vTaskFunction13(void *pvParameters)
{
    while(1)
    {
        // Получаем приоритет текущей задачи
        UBaseType_t uxPriority = uxTaskPriorityGet(NULL);

        // Проверка границ приоритетов
        UBaseType_t uxMaxPriority = configMAX_PRIORITIES-1;  // Максимальный приоритет
        UBaseType_t uxMinPriority = tskIDLE_PRIORITY;  // Минимальный приоритет

        // Логика для вычисления нового приоритета
        UBaseType_t uxNewPriority = uxPriority;
        if ((uxPriority + 1) <= uxMaxPriority) {
            uxNewPriority = uxPriority + 1;  // Увеличиваем приоритет, если это не выходит за границы
        } else if ((uxPriority - 1) >= uxMinPriority) {
            uxNewPriority = uxPriority - 1;  // Уменьшаем приоритет, если это не выходит за границы
        }

        char buf[100];
        sprintf(buf, "Old priority: %lu.\nNew priority: %lu.\nPriority limits: %lu .. %lu.\n", uxPriority, uxNewPriority, uxMinPriority, uxMaxPriority);
        vSendString(buf);
        
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}

int task13(void)
{
    // Создание задачи
    xTaskCreate(vTaskFunction13, "Task", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Запуск планировщика
    vTaskStartScheduler();

    return 0;
}
