#include <stdio.h>

int main() {

    printf("characters %c%c%c\n", 'a', '\t', '1');
    /* %d and %i behaves same for printf but differently for scanf */
    printf("integers %d %i %i\n", 3, 04, 0xA);
    /* you can use type casting or arithmetic operations */
    printf("floating points %f %e\n", 2.5, (double)1000);
    printf("floating point precision %.2f\n", 3.1415);
    printf("floating point arithmetic %.10f\n", 1.0/7);

    printf("%f\n", 3.0);
    return 0;
}
