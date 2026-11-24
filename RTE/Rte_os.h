#ifndef RTE_OS_H
#define RTE_OS_H

/* ================= Inicializacion del OS ================= */
void Rte_Start(void);

/* ================= Prototipos de Tareas ================= */
void OsTask_diag(void *p1, void *p2, void *p3);
void OsTask_app(void *p1, void *p2, void *p3);
void OsTask_comm_tx(void *p1, void *p2, void *p3);
void OsTask_comm_rx(void *p1, void *p2, void *p3);

#endif /* RTE_OS_H */