#include "includes/ping.h"

void send_ping(t_conf *conf, t_stats *stats, t_opt *opt){

    char packet[PACKET_LEN];

    memset(packet, 0, PACKET_LEN);
    memset(&conf->start_timestamp, 0, sizeof(conf->start_timestamp));
    gettimeofday(&conf->start_timestamp,NULL);

    fill_packet(packet, conf);

    if (opt->verbose)
        memcpy(conf->packet_sent, packet, PACKET_LEN);
    
    if (sendto(conf->sockfd, &packet, PACKET_LEN, 0, (const struct sockaddr*)&conf->dest, sizeof(struct sockaddr))< 0){
        exit(1);
    }
    stats->nb_packets_transmitted++;
    return;
}