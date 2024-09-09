#include "includes/ping.h"

void send_ping(t_conf *conf){

    char packet[PACKET_LEN];
    memset(packet, 0, PACKET_LEN);

    gettimeofday(&conf->start_timestamp, NULL);

    fill_ip_header((struct ip*)packet, conf);
    fill_payload((char*)&packet);
    fill_icmp_msg((struct icmp*)(&packet[IP_HEADER_LEN]), conf);

    // print_packet(packet);

    if (sendto(conf->sockfd, &packet, PACKET_LEN, 0, (const struct sockaddr*)&conf->dest, sizeof(struct sockaddr))< 0)
        perror("send status ");
}