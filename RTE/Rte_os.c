#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "Rte_os.h"

#define STACK_SIZE_THREAD_DIAG    1024

K_THREAD_STACK_DEFINE(stack_diag, STACK_SIZE_THREAD_DIAG);

#define PRIORIDAD_DIAG            5

static struct k_thread thread_diag_data;

void OsTask_diag(void *p1, void *p2, void *p3)
{
    while (1)
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
    k_tid_t tid_diag = k_thread_create(
        &thread_diag_data,
        stack_diag,
        K_THREAD_STACK_SIZEOF(stack_diag),
        OsTask_diag,
        NULL, NULL, NULL,
        PRIORIDAD_DIAG,
        0,
        K_NO_WAIT);

    // Nombre task
    k_thread_name_set(tid_diag, "Task_diag");
}