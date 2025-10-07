#include "calc.h"
#include <stdio.h>   // para printf
#include <stdlib.h>  // por si usas exit()

// SUMA
int *suma_1_svc(intpair *par, struct svc_req *rqstp) {
    static int res;
    res = par->a + par->b;
    printf("[SERVIDOR] Solicitud SUMA: %d + %d = %d\n", par->a, par->b, res);
    return &res;
}

// RESTA
int *resta_1_svc(intpair *par, struct svc_req *rqstp) {
    static int res;
    res = par->a - par->b;
    printf("[SERVIDOR] Solicitud RESTA: %d - %d = %d\n", par->a, par->b, res);
    return &res;
}

// MULTIPLICA
int *multiplica_1_svc(intpair *par, struct svc_req *rqstp) {
    static int res;
    res = par->a * par->b;
    printf("[SERVIDOR] Solicitud MULTIPLICA: %d * %d = %d\n", par->a, par->b, res);
    return &res;
}

// DIVIDE
float *divide_1_svc(intpair *par, struct svc_req *rqstp) {
    static float res;
    if (par->b != 0)
        res = (float)par->a / par->b;
    else
        res = 0.0;
    printf("[SERVIDOR] Solicitud DIVIDE: %d / %d = %.2f\n", par->a, par->b, res);
    return &res;
}
