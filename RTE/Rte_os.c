#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "Rte_os.h"

/* ================= Configuracion de Threads ================= */
#define STACK_SIZE_THREAD_APP   1024
#define PRIORIDAD_APP           5

#define STACK_SIZE_THREAD_COMM  1024
#define PRIORIDAD_COMM          5

/* ================= Stacks y Estructuras ================= */
static K_THREAD_STACK_DEFINE(stack_app, STACK_SIZE_THREAD_APP);
static struct k_thread thread_app_data;
static k_tid_t tid_app;

static K_THREAD_STACK_DEFINE(stack_comm, STACK_SIZE_THREAD_COMM);
static struct k_thread thread_comm_data;
static k_tid_t tid_comm;

/* ================= Tareas (Tasks) ================= */
void OsTask_app(void *p1, void *p2, void *p3)
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

        /* Ajusta este periodo segun la logica de tu aplicacion */
        k_msleep(100);
    }
}

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

/* ================= Inicializacion del OS ================= */
void Rte_Start(void)
{
    /* Crear tareas suspendidas para asignarles nombre antes de iniciar */
    tid_app = k_thread_create(&thread_app_data,
                              stack_app,
                              K_THREAD_STACK_SIZEOF(stack_app),
                              OsTask_app,
                              NULL, NULL, NULL,
                              PRIORIDAD_APP,
                              0,
                              K_FOREVER);

    tid_comm = k_thread_create(&thread_comm_data,
                               stack_comm,
                               K_THREAD_STACK_SIZEOF(stack_comm),
                               OsTask_comm_rx,
                               NULL, NULL, NULL,
                               PRIORIDAD_COMM,
                               0,
                               K_FOREVER);

    /* Requiere CONFIG_THREAD_NAME=y en prj.conf */
    k_thread_name_set(tid_app, "Task_app");
    k_thread_name_set(tid_comm, "Task_comm_rx");

    /* Arrancar tareas */
    k_thread_start(tid_app);
    k_thread_start(tid_comm);
}