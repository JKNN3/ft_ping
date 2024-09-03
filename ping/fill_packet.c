#include "includes/ping.h"

void    fill_ip_header(struct ip *ip_header, t_data *ping_conf){
    ip_header->ip_hl = IP_HEADER_LEN_IN_32BITS_INCREMENT;
    ip_header->ip_v = IP_VERSION;
    ip_header->ip_tos = 0;
    ip_header->ip_len = htons(IP_HEADER_LEN);
    ip_header->ip_id = htons(IP_ID);
    ip_header->ip_off = 0;//    htons(SET_THE_DONT_FRAGMENT_THE_PACKET_BIT_TO_TRUE);
    ip_header->ip_ttl = TIME_TO_LIVE;
    ip_header->ip_p = IPPROTO_ICMP;
    ip_header->ip_sum = 0;
    ip_header->ip_src.s_addr = INADDR_ANY;
    ip_header->ip_dst.s_addr = ((struct sockaddr_in*)&ping_conf->dest)->sin_addr.s_addr;
    ip_header->ip_sum = compute_checksum((void*)ip_header, IP_HEADER_LEN);
}


void    fill_icmp_msg(struct icmp *icmp_msg){
    icmp_msg->icmp_type = ICMP_ECHO;
    icmp_msg->icmp_code = ICMP_ECHOREPLY;
    icmp_msg->icmp_cksum = 0;
    icmp_msg->icmp_id = 2; // mike muss did : in = getpid() & 0xFFFF pour avoir juste les 16 derniers bits
                                // car c'est un u_int_16. C'est important poiur l'identification du paquet retour;
    icmp_msg->icmp_seq= 3; // nombre de paquets transmis, a ++ quand on envoie un paquet, struct principale.

     void *icmp_timeval = (void*)icmp_msg + ICMP_HEADER_LEN;
     if (gettimeofday((struct timeval *)icmp_timeval, NULL) < 0)
         perror("gettimeofday failed filling icmp message ");

    icmp_msg->icmp_cksum = compute_checksum((void *)icmp_msg, ICMP_HEADER_LEN); // -> u_int16_t 2 bytes mais quand on a fini de remplir la struct huh

    /* payload 40 bytes */

}