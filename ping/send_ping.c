#include "includes/ping.h"

void send_ping(t_conf *conf, t_stats *stats){

    char packet[PACKET_LEN];

    memset(packet, 0, PACKET_LEN);
    memset(&conf->start_timestamp, 0, sizeof(conf->start_timestamp));

    gettimeofday(&conf->start_timestamp,NULL);

    fill_ip_header((struct ip*)packet, conf);
    fill_payload((char*)&packet);
    fill_icmp_msg((struct icmp*)(&packet[IP_HEADER_LEN]), conf);

    if (sendto(conf->sockfd, &packet, PACKET_LEN, 0, (const struct sockaddr*)&conf->dest, sizeof(struct sockaddr))< 0){
        perror("ft_ping : sending packets ");
        exit(1);
    }
    stats->nb_packets_transmitted++;
    return;
}