#include "includes/ping.h"

short compute_checksum(void *packet, int len){ // len = longueur du packet en octets/bytes
    short   *tmp = packet; 
    int     sum;

    while (len > 1){
        sum += *tmp++;
        len -=2;
    }
    if (len == 1)
        sum += *((char *)packet);
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum << 16);
    return (~((short)sum));
}