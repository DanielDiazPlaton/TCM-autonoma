#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "Rte_os.h"

/* ================= Configuracion de Threads ================= */
#define STACK_SIZE_THREAD_APP       1024
#define PRIORIDAD_APP               5
#define PERIODO_APP_MS              100

#define STACK_SIZE_THREAD_COMM_TX   1024
#define PRIORIDAD_COMM_TX           5
#define PERIODO_COMM_TX_MS          20

#define STACK_SIZE_THREAD_COMM_RX   1024
#define PRIORIDAD_COMM_RX           5
#define PERIODO_COMM_RX_MS          20

/* ================= Stacks y Estructuras ================= */
static K_THREAD_STACK_DEFINE(stack_app, STACK_SIZE_THREAD_APP);
static struct k_thread thread_app_data;
static k_tid_t tid_app;

static K_THREAD_STACK_DEFINE(stack_comm_tx, STACK_SIZE_THREAD_COMM_TX);
static struct k_thread thread_comm_tx_data;
static k_tid_t tid_comm_tx;

static K_THREAD_STACK_DEFINE(stack_comm_rx, STACK_SIZE_THREAD_COMM_RX);
static struct k_thread thread_comm_rx_data;
static k_tid_t tid_comm_rx;

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

        k_msleep(PERIODO_APP_MS);
    }
}

void OsTask_comm_tx(void *p1, void *p2, void *p3)
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

        k_msleep(PERIODO_COMM_TX_MS);
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

        k_msleep(PERIODO_COMM_RX_MS);
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

    tid_comm_tx = k_thread_create(&thread_comm_tx_data,
                                  stack_comm_tx,
                                  K_THREAD_STACK_SIZEOF(stack_comm_tx),
                                  OsTask_comm_tx,
                                  NULL, NULL, NULL,
                                  PRIORIDAD_COMM_TX,
                                  0,
                                  K_FOREVER);

    tid_comm_rx = k_thread_create(&thread_comm_rx_data,
                                  stack_comm_rx,
                                  K_THREAD_STACK_SIZEOF(stack_comm_rx),
                                  OsTask_comm_rx,
                                  NULL, NULL, NULL,
                                  PRIORIDAD_COMM_RX,
                                  0,
                                  K_FOREVER);

    /* Asignar nombres (requiere CONFIG_THREAD_NAME=y en prj.conf) */
    k_thread_name_set(tid_app, "Task_app");
    k_thread_name_set(tid_comm_tx, "Task_comm_tx");
    k_thread_name_set(tid_comm_rx, "Task_comm_rx");

    /* Arrancar todas las tareas */
    k_thread_start(tid_app);
    k_thread_start(tid_comm_tx);
    k_thread_start(tid_comm_rx);
}