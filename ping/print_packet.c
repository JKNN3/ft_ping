#include "includes/ping.h"

static void fill_buffer_with_ip_hexdump(char *buffer, char *packet, int len);
static void fill_buffer_with_icmp_packet(char *buffer, struct ip *packet);

void    print_packet_dump(char *packet){
    char buffer[250];
    memset(&buffer, 0, sizeof(buffer));
    int len = 0;
    len += sprintf(&buffer[len], PACKET_DUMP_IP_HEADER);
    fill_buffer_with_ip_hexdump(&buffer[len], packet, IP_HEADER_LEN);
    len += IP_HEADER_LEN;
    len += sprintf(&buffer[len], PACKET_DUMP_IP_DETAILS);
    fill_buffer_with_icmp_packet(&buffer[len],(struct ip*)packet);
    printf("%s", packet);
}

static void fill_buffer_with_ip_hexdump(char *buffer, char *packet, int len){
    unsigned char data;
    for (int i = 0; i < len; i++){ // print in hexa
        if (i % 8 == 0)
            sprintf(buffer, "  ");
        if (i % 16 == 0)
            sprintf(buffer, "\n");
        data = ((unsigned char*)packet)[i];
        sprintf(buffer, "%02x ", data);
    }
    printf ("\n");
}

static void fill_buffer_with_icmp_packet(char *buffer, struct ip *packet){
    printf("icmp_vr %c: icmp hl: %c\n", packet->ip_v, packet->ip_hl);
}

