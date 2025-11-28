#!/bin/bash

mkdir -p logs
mkdir -p traces

# Список задач
TASKS=(11 12)
# 11 12 13 14 15 21 22 23 24 25 26 27 28 31 32 41 42 43 44 45 46 51 52 53 54

for TASK in "${TASKS[@]}"; do
    echo "Компиляция задачи TASK_NN=$TASK"
    make clean
    make TASK_NUMBER=$TASK
    echo "Запуск задачи TASK_NN=$TASK"
    qemu-system-riscv32 -machine virt -serial stdio -display none -bios none -kernel build/RTOSDemo.axf -trace riscv_trap -d int -D traces/${TASK}.log > logs/${TASK}.txt &

    # Получаем PID процесса, Ctrl+C через 5 секунд
    PID=$!
    sleep 5
    kill -SIGINT $PID
done
