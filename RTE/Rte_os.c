#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "Rte_os.h"

#define STACK_SIZE_THREAD_COMM 1024

static K_KERNEL_STACK_DEFINE(stack_comm, STACK_SIZE_THREAD_COMM);

#define PRIORIDAD_COMM 5

static struct k_thread thread_comm_data;

void OsTask_comm_rx(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

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
    tid_comm = k_thread_create(&thread_comm_data,          /* bloque de control */
                               stack_comm,                 /* stack */
                               K_THREAD_STACK_SIZEOF(stack_comm),
                               OsTask_comm_rx,                /* función de entrada */
                               NULL, NULL, NULL,           /* p1, p2, p3 */
                               PRIORIDAD_COMM,             /* prioridad */
                               0,                          /* opciones */
                               K_NO_WAIT);                 /* arranca de inmediato */

    k_thread_name_set(tid_comm, "Task_comm_rx");

}