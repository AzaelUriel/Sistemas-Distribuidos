/* calc.x */
program CALC_PROG {
    version CALC_VERS {
        int SUMA(intpair) = 1;
        int RESTA(intpair) = 2;
        int MULTIPLICA(intpair) = 3;
        float DIVIDE(intpair) = 4;
    } = 1;
} = 0x31234567;

struct intpair {
    int a;
    int b;
};
