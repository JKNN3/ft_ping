#include "includes/ping.h"

static int  fill_buffer_with_ip_hexdump(char *buffer, char *packet);
static int  fill_buffer_with_ip_header_infos(char *buffer, struct ip *ip, char *src_ip);
static int fill_buffer_with_icmp_infos(char *buffer, struct icmp *icmp);


void    print_packet_sent_dump(char *packet_sent, char *src_ip){


    struct ip *ip = (struct ip*)packet_sent;
    struct icmp *icmp = (struct icmp*)&packet_sent[IP_HEADER_LEN];

    char buffer[800];
    memset(&buffer, 0, sizeof(buffer));
    int len = 0;
    len += sprintf(&buffer[len], PACKET_DUMP_IP_HEADER);
    len += fill_buffer_with_ip_hexdump(&buffer[len], (char*)ip);
    len += fill_buffer_with_ip_header_infos(&buffer[len], ip, src_ip);

    len += fill_buffer_with_icmp_infos(&buffer[len], icmp);
    printf("%s", buffer);
}

static int fill_buffer_with_ip_hexdump(char *buffer, char *packet){

    char *start = buffer;

    for (int i = 0; i < IP_HEADER_LEN; i += 2){
        buffer += (unsigned char)sprintf(buffer, "%02x%02x ", \
        ((unsigned char*)packet)[i], ((unsigned char*)packet)[i + 1]);
    }
    buffer += (unsigned char)sprintf (buffer, "\n");

    return (buffer- start);
}

static int  fill_buffer_with_ip_header_infos(char *buffer, struct ip *ip, char* src_ip){

    int len = 0;

    len += sprintf(&buffer[len], PACKET_DUMP_IP_DETAILS);
    len += sprintf(&buffer[len], " %d  %d  %02x %04x %04x %3d %04x  %02x  %02x %04x %s  ", \
    ip->ip_v, ip->ip_hl, ip->ip_tos, ntohs(ip->ip_len), ntohs(ip->ip_id), 0, ntohs(ip->ip_off), \
    ip->ip_ttl, ip->ip_p, ntohs(ip->ip_sum), src_ip);
    
    len += sprintf(&buffer[len],"%s\n",  inet_ntoa(*(struct in_addr *)&ip->ip_dst));
    printf("%ld\n", buffer-(&buffer[len]));
    return (&buffer[len] - buffer);
}

static int fill_buffer_with_icmp_infos(char *buffer, struct icmp *icmp){

    int len = 0;

    len += sprintf(&buffer[len], "ICMP: type %u, code %u, size %d, id 0x%04x , seq 0x%04x\n", \
    icmp->icmp_type, icmp->icmp_code, ICMP_MSG_LEN, ntohs(icmp->icmp_id), ntohs(icmp->icmp_seq));

    return (len);
}

