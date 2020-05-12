#include <stdio.h>

int main() {

    char c1, c2;
    int i1, i2;
    long int li1;
    float f1, f2;
    double d1, d2;
    long double ld1;

    printf("enter 3 integers, \n\ttry negative/positive decimal/octal/hexadecimal, \n\ttry -1 for all\n");
    scanf("%d %i %ld", &i1, &i2, &li1);
    printf("d:%d i:%i u:%u o:%o x:%x\n", i1, i1, i1, i1, i1);
    printf("d:%d i:%i u:%u o:%o x:%X\n", i2, i2, i2, i2, i2);
    printf("ld:%ld li:%li lu:%lu lo:%lo lx:%lx\n", li1, li1, li1, li1, li1);

    printf("enter 2 characters, letter/digit/punctuation, separate with a space or not, \n\tenter more than 2 and see what happens\n");
    printf("\ttry \" %%c %%c\" \"%%c%%c\" \" %%c %%c \" \"%%c %%c \" etc. with spaces\n");
    scanf("%c %c", &c1, &c2);
    printf("c:%c d:%d c:%c d:%d\n", c1, c1, c2, c2);

    printf("enter 4 floating points\n");
    scanf("%f %f %f %f", &f1, &f2, &d1, &d2);
    printf("%f %f %f %f \n", f1, f2, d1, d2);
    printf("%e %e %e %e \n", f1, f2, d1, d2);
    
    printf("enter 4 more floating points, this time with exponents\n");
    scanf("%e %e %e %e", &f1, &f2, &d1, &d2);
    printf("%f %f %f %f \n", f1, f2, d1, d2);
    printf("%e %e %e %e \n", f1, f2, d1, d2);
    
    ld1 = d1 * d2;
    printf("Lf/Le/LE for long double: %lf %le %lE\n", ld1, ld1, ld1);

    return 0;
}
