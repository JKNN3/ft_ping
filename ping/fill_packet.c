#include "includes/ping.h"

static void    fill_payload(char *packet);
static void    fill_icmp_msg(struct icmp *packet, t_conf *conf);
static void    fill_ip_header(struct ip *packet, t_conf *conf);

void    fill_packet(char *packet, t_conf *conf){

    fill_ip_header((struct ip*)packet, conf);
    fill_payload((char*)&packet);
    fill_icmp_msg((struct icmp*)(&packet[IP_HEADER_LEN]), conf);

}

// fill the IP HEADER part of the packet (IP_HEADER_LEN = 20 bytes)
static void    fill_ip_header(struct ip *packet, t_conf *conf){

    packet->ip_hl = IP_HEADER_LEN_IN_32BITS_INCREMENT;
    packet->ip_v = IP_VERSION;
    packet->ip_tos = 0;
    packet->ip_len = htons(IP_HEADER_LEN);
    packet->ip_id = htons(conf->id & 0xFFFF);
    short off = 0;
    off = SET_THE_DONT_FRAGMENT_THE_PACKET_BIT_TO_TRUE;
    packet->ip_off = htons(off);
    packet->ip_ttl = conf->ttl;
    packet->ip_p = IPPROTO_ICMP;
    packet->ip_sum = 0;
    packet->ip_src.s_addr = INADDR_ANY;
    packet->ip_dst.s_addr = conf->dest.sin_addr.s_addr;
    packet->ip_sum = compute_checksum((void*)packet, IP_HEADER_LEN);
}

// fill the ICMP MESSAGE part of the packet ()
static void    fill_icmp_msg(struct icmp *packet, t_conf *conf){

    packet->icmp_type = ICMP_ECHO;
    packet->icmp_code = ICMP_ECHOREPLY;
    packet->icmp_cksum = 0;
    packet->icmp_id = (conf->id & 0xFFFF);
    packet->icmp_seq= ++(conf->seq);

     void *icmp_timeval = (void*)packet + ICMP_HEADER_LEN;
     if (gettimeofday((struct timeval *)icmp_timeval, NULL) < 0)
         perror("gettimeofday failed filling icmp message ");

    packet->icmp_cksum = compute_checksum((void *)packet, ICMP_MSG_LEN);
}

// fill the rest of the packet with payload data (40 bytes)
static void    fill_payload(char *packet){
    
    for(int i = (ICMP_PAYLOAD_STARTING_BYTE); i < PACKET_LEN; i++){
        packet[i] = i + '0';
    }
}