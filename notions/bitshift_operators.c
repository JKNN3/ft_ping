/*              BITSHIFT OPERATORS

    nb << 1 multiplies nb by 2 and nb >> 1 divide nb by 2 (faster than * and /)

    left shifting :
(nb) << (bits) seems to multiply our number by the power of bits
    ex : 5 (00000101) << 1 -> 5*2^1 ou 10 (00001010);
the first bit of a number stores the sign so be careful (and with big numbers too)

    right shifting:
with signed integers, the right shift takes a look to the sign, in most compilers, it shift everything to the right
and put a 1 if it's a negative number (or a 0 if it's positive) to the sign bit (first bit)

we can : nb <<= 2

*/
#include  <stdio.h>

int main(int argc, char **argv){
    int a = -100000;
    /*      left shifting       */
    printf("left shifted by 1: %d\n", a <<= 1);
    printf("left shifted by 1: %d\n", a << 2);
    printf("left shifted by 1: %d\n", a << 3);
    // for ( int i = 0; i < 32; i++){
    //     printf("left shifted by %02d: %08x | %u\n", i, a<<i, a<<i);
    // }

    /*      right shifting      */
    printf("left shifted by 1: %d\n", a >> 1);
    printf("left shifted by 1: %d\n", a >> 2);
    printf("left shifted by 1: %d\n", a >> 3);
    // for ( int i = 0; i < 32; i++){
    //     printf("left shifted by %02d: %x | %d\n", i, a >> i, a >> i);
    // }

    return 0;
}