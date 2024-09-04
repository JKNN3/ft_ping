#include "includes/ping.h"

void    print_packet(char *packet){
    unsigned char data;
    for (int i = 0; i < PACKET_LEN; i++){ // print in hexa
        if (i % 8 == 0)
            printf ("  ");
        if (i % 16 == 0)
            printf ("\n");
        data = ((unsigned char*)packet)[i];
        printf("%02x ", data);
    }
    printf ("\n");
}