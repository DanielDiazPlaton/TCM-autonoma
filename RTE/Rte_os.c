#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "Rte_os.h"

#define STACK_SIZE_THREAD_APP 1024
K_THREAD_STACK_DEFINE(stack_app,STACK_SIZE_THREAD_APP );

#define PRIORIDAD_APP 5

static struct k_thread thread_app_data;

void OsTask_app(void *p1, void *p2, void *p3)
{

    while(1)
    {
        const char *tname = k_thread_name_get(k_current_get());
        printk("%lld ms] Ejecutando thread: %s, Prioridad: %d\n",
        k_uptime_get(),
        tname ? tname : "unnamed",
        k_thread_priority_get(k_current_get()));
        k_msleep(20);
    }
}

void Rte_Start(void)
{
    
    k_tid_t tid_app = k_thread_create(
        &thread_app_data,
        stack_app,
        K_THREAD_STACK_SIZEOF(stack_app),
        OsTask_app,
        NULL, NULL, NULL,
        PRIORIDAD_APP,
        0,
        K_NO_WAIT);


    k_thread_name_set(tid_app, "Task_APP");
}