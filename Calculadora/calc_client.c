#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

static void calc_prog_1(const char *host, int a, int b) {
    CLIENT *clnt = clnt_create(host, CALC_PROG, CALC_VERS, "udp");
    if (!clnt) { clnt_pcreateerror(host); exit(1); }

    intpair args;
    args.a = a;
    args.b = b;

    int *sum = suma_1(&args, clnt);
    int *res = resta_1(&args, clnt);
    int *mul = multiplica_1(&args, clnt);
    float *div = divide_1(&args, clnt);

    printf("Suma: %d\n", *sum);
    printf("Resta: %d\n", *res);
    printf("Multiplica: %d\n", *mul);
    printf("Divide: %.2f\n", *div);

    clnt_destroy(clnt);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <host> <a> <b>\n", argv[0]);
        exit(1);
    }
    calc_prog_1(argv[1], atoi(argv[2]), atoi(argv[3]));
    return 0;
}
