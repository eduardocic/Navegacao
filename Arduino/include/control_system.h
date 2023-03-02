#ifndef _CONTROL_SYSTEM_H_
#define _CONTROL_SYSTEM_H_

/* Estrutura de dados com as variáveis que rodam na função principal de Kalman */
typedef struct {
    matrix *PHIk_t;             /* Transposta de PHIk, ou seja, (PHIk)'                */
    matrix *Mk;                 /* Variável derivada na EQ. 1                          */
    matrix *H_t;                /* Transposta de H, ou seja, (H)'                      */
    matrix *temp_nxp;           /* Variável de auxílio aos cálculos                    */
    matrix *temp_nxn;           /* Variável de auxílio aos cálculos                    */
    matrix *temp_pxn;           /* Variável de auxílio aos cálculos                    */
    matrix *soma;               /* Matriz soma na EQ. 2 que fará a inversão            */
    matrix *inv_soma;           /* Matriz inversa da soma                              */
    matrix *Inxn;               /* Ponteiro para uma matriz identidade de dimensão nxn */
} KALMAN_s;

/*   FILTRO DE KALMAN   */
/* ==================== */
void kalman_init(int n, int p, KALMAN_s *ptr);					/* Função 'kalman_init': chamada por 'kalman       */
void kalman(matrix *P_k_1, matrix *PHI_k, matrix *Q_k, 
            matrix *R_k, matrix *H, matrix *K_k);				/* Função 'kalman': função de kalman               */


#endif