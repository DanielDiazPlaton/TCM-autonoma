#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "Rte_os.h"

#define STACK_SIZE_THREAD_COMM_TX        1024

K_THREAD_STACK_DEFINE(stack_comm_tx, STACK_SIZE_THREAD_COMM_TX);

#define PRIORIDAD_COMM_TX        5

static struct k_thread thread_comm_tx_data;

void OsTask_comm_tx(void *p1, void *p2, void *p3)
{
    while(1)
    {
        const char *tname = k_thread_name_get(k_current_get());
        printk("[%lld ms] Ejecutando thread: %s, Prioridad: %d\n",
            k_uptime_get(),
            tname ? tname : "unnamed",
            k_thread_priority_get(k_current_get()));
        k_msleep(20);
    }
}

void Rte_Start(void)
{
    // Inicializacion del OS
    k_tid_t tid_comm_tx = k_thread_create(
        &thread_comm_tx_data,
        stack_comm_tx,
        K_THREAD_STACK_SIZEOF(stack_comm_tx),
        OsTask_comm_tx,
        NULL, NULL, NULL,
        PRIORIDAD_COMM_TX,
        0,
        K_NO_WAIT);

    //Nombre task
    k_thread_name_set(tid_comm_tx, "Task_comm_tx");
}