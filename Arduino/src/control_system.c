#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "control_system.h"
#include "matematica.h"


void kalman(matrix *P_k_1, matrix *PHI_k, matrix *Q_k, matrix *R_k, matrix *H, matrix *K_k){
/* =========================================================================
 *
 *  REFERẼNCIA: Fundamentals of Kalman Filtering: A Practical Approach, 
 * ============ 3th Edition
 *              Paul Zarchan & Howard Musoff
 *              Página 131
 *
 *
 *  EQUAÇÕES A SE RESOLVER:
 * ========================
 *
 *  ---> Mk = PHI_k * P_k_1 * (PHI_k)' + Q_k             (EQ. 1)
 *  ---> K_k = Mk * (H)' * inv{(H * Mk * (H)' + R_k)}    (EQ. 2)
 *  ---> P_k = (I - K_k * H) * Mk                        (EQ. 3)
 *
 *
 *  ENTRADAS:
 * ==========
 *
 *    1. P_k_1 ..........: tem dimensão 'n x n';
 *    2. PHI_k ..........: tem dimensão 'n x n';
 *    3. Q_k ............: tem dimensão 'n x n';
 *    4. R_k ............: tem dimensão 'p x p';
 *    5. H ..............: tem dimensão 'p x n';
 *    6. K_k ............: tem dimensão 'n x p'; e
 *    7. ptr ............: ponteiro para estrutura do tipo 'KALMAN_s'.
 *
 * Eduardo H. Santos
 * 25/01/2023
 * ======================================================================= */

    /* Necessária definição da estrutura de Kalman */
    /* =========================================== */
    static booleano flag = FALSO;
    static KALMAN_s ptr = { .PHIk_t   = NULL, 
                            .Mk       = NULL,
                            .H_t      = NULL, 
                            .temp_nxp = NULL,
                            .temp_nxn = NULL, 
                            .temp_pxn = NULL, 
                            .soma     = NULL, 
                            .inv_soma = NULL, 
                            .Inxn     = NULL};

    /* Inicializa as variáveis static a serem utilizadas apenas dentro aqui */
    /* ==================================================================== */
    if (!flag){
        /* Variáveis auxiliares */    
        int n = P_k_1->lines;
        int p = H->lines;

        /* Inicialização dos parâmetros de Kalman */
        kalman_init(n, p, &ptr);

        /* Faz a operação de transposição de matrizes pertinentes */
        transpose(PHI_k, ptr.PHIk_t);
        transpose(    H, ptr.H_t   );
        flag = VERDADEIRO;
    }

    /* (EQ. 1)    Mk = PHI_k * P_k_1 * (PHI_k)' + Q_k    */
    /* ================================================= */
    prod(       PHI_k,      P_k_1, ptr.temp_nxn);
    prod(ptr.temp_nxn, ptr.PHIk_t,       ptr.Mk);
    add(       ptr.Mk,        Q_k,       ptr.Mk);

    /* (EQ. 2)  Mk * (H)' * inv{(H * Mk * (H)' + R_k)}   */
    /* ================================================= */
    prod(            H,         ptr.Mk,  ptr.temp_pxn);
    prod( ptr.temp_pxn,        ptr.H_t,      ptr.soma);
    add(      ptr.soma,            R_k,      ptr.soma);
    inv(      ptr.soma,  ptr.inv_soma);
    prod(       ptr.Mk,        ptr.H_t,  ptr.temp_nxp);
    prod( ptr.temp_nxp,   ptr.inv_soma,           K_k);

    /* (EQ. 3)     P_k = (I - K_k * H) * Mk              */
    /* ================================================= */
    prod(          K_k,        H,         P_k_1);
    sub(      ptr.Inxn,    P_k_1,  ptr.temp_nxn); 
    prod( ptr.temp_nxn,   ptr.Mk,         P_k_1);
}





void kalman_init(int n, int p, KALMAN_s *ptr){
/* =========================================================================
 * Inicialização de estrutura do tipo 'KALMAN_s' com parâmetros estáticos
 * os quais são utilizados recursivamente pela função de 'kalman'
 * ======================================================================= */
 
	/* Aloca espaço para matrizes utilizadas no programa. */
	matrix *PHIk_t    = new_matrix(n, n);
	matrix *Mk        = new_matrix(n, n);
	matrix *H_t       = new_matrix(n, p);
	matrix *temp_nxp  = new_matrix(n, p);
	matrix *temp_nxn  = new_matrix(n, n);
	matrix *temp_pxn  = new_matrix(p, n);
	matrix *soma      = new_matrix(p, p);  
	matrix *inv_soma  = new_matrix(p, p); 
	matrix *Inxn      = eye(n);

	/* Faz o ponteiro apontar para as variáveis */
	ptr->PHIk_t    = PHIk_t;
	ptr->Mk        = Mk;
	ptr->H_t       = H_t;
	ptr->temp_nxp  = temp_nxp;
	ptr->temp_nxn  = temp_nxn;
	ptr->temp_pxn  = temp_pxn;
	ptr->soma      = soma;
	ptr->inv_soma  = inv_soma;
	ptr->Inxn      = Inxn;
}            