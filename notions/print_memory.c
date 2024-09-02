/*              PRINT MEMORY                

0c 00 00 00 (0c = 12 in hexa)  
6b 74 65 73 (6b = k, 74 65 73 .. is testing in ascii hexa)
74 69 6e 67 
00 00 00 00 
6c 90 2b 8d 
fd 7f 00 00 (inverted bcs little endian so bytes (and not bits) are inverted)
00 01 00 00 (same so not 00 01 but 01 00 => 1*16^2 (just hexa to decimal) = 256)
00 00 00 00 

    memory padding is adding bytes to memory you allocate so the cpu can be faster
    the compiler tries to align every single element at 8 bytes (64 bits)

    #pragma pack(1) unaligned the memory and allocate just what is needed.
        pack(1) says "align everything on one byte" so dont align anything bcs smallest unity

*/
#include <stdio.h>
#include <stdlib.h>

// typedef struct {
//     int     test;       // 4 bytes
//     char    k;          // 1
//     char    str[10];    // 10
//     int     *p;         // 8
//     short   sh;         // 2
// } t_thing;      // total : 25 bytes but we have 32 for memory alignment

int print_memory(char *memory){
    int i;
    printf("sizeof t: %lu\n", sizeof(memory));
    unsigned char data;
    for (i = 0; i < sizeof(memory); i++){ // print in hexa
        if (i % 4 == 0)
            printf ("\n");
        data = ((unsigned char*)&memory)[i];
        printf("%02x ", data);
    }
    printf ("\n");

    // for (i = 0; i < sizeof(memory); i++){ // print in decimal
    //     if (i % 4 == 0)
    //         printf ("\n");
    //     data = ((unsigned char*)&memory)[i];
    //     printf("%03hhu ", data);
    // }
    // printf ("\n");
    // for (i = 0; i < sizeof(memory); i++){ // print in characters
    //     if (i % 4 == 0)
    //         printf ("\n");
    //     data = ((unsigned char*)&memory)[i];
    //     printf("%c ", data);
    // }
    // printf ("\n");
    return 0; 
}