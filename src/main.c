/* Simple program to examine how are different data types encoded in memory */

#include <stdio.h>

/*
 * The macro determines size of given variable and then
 * prints individual bytes of the value representation
 */
#define PRINT_MEM(a) print_mem((unsigned char*)&(a), sizeof(a))

void print_float(void *val) {

    unsigned const converted = *(unsigned*)val;


    unsigned mask = 1 << 31;
    printf("%c  ", converted & mask ? '1' : '0');

    int bits = 1;

    mask >>= 1;
    for (int exp = 0; exp < 8; mask >>= 1, ++exp) {
        printf("%c", converted & mask ? '1' : '0');
        if (++bits == 4) {
            bits = 0;
            printf("'");
        }
    }

    printf("  ");
    for (int mantissa = 0; mantissa < 23; mask >>= 1, ++mantissa) {
        printf("%c", converted & mask ? '1' : '0');
        if (++bits == 4) {
            printf("'");
            bits = 0;
        }
    }
    printf("\n");

}

void print_mem(unsigned char* ptr, int size) {
    printf("address = 0x%016lx:\t", (long unsigned int)ptr);

    for (int i = 0; i < size; i++) {
        printf("0x%02x ", ptr[i]); // == printf("0x%02x ", ptr[i]);
    }

    printf("\n");
}

int main() {
    /* try for more types: long, float, double, pointer */
    unsigned int unsig = 5;
    int sig = -5;

    /* Read GNU C Library manual for conversion syntax for other types */
    /* https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html */
    /*printf("value = %d\n", unsig);
    PRINT_MEM(unsig);

    printf("\nvalue = %d\n", sig);
    PRINT_MEM(sig);
    */
    for (float volatile val = 0.0f; val < 1000000.0f; val += 1.0f) {
        printf("%6d:   ", (int)val);
        print_float(&val);
    }


    return 0;
}