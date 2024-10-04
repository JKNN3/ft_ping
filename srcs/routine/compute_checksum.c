#include "ping.h"

short compute_checksum(void *packet, int len){
    unsigned short   *tmp = packet;
    unsigned int      sum = 0;

    while (len > 1){
        sum += *tmp++;
        len -=2;
    }
    if (len == 1)
        sum += *((char *)packet);
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (((unsigned short)~sum));
}