#include "../../includes/ping.h"

static void if_flood_print_point(t_opt *opt);
static void if_verbose_copy_packet_for_print(bool verbose, t_conf *conf, char *packet);

void send_ping(t_conf *conf, t_stats *stats, t_opt *opt){

    char packet[PACKET_LEN];

    memset(packet, 0, PACKET_LEN);
    memset(&conf->start_timestamp, 0, sizeof(conf->start_timestamp));
    gettimeofday(&conf->start_timestamp,NULL);

    fill_packet(packet, conf);
    if_verbose_copy_packet_for_print(opt->verbose, conf, packet);
    
    if (sendto(conf->sockfd_send, &packet, PACKET_LEN, 0, (const struct sockaddr*)&conf->dest_addr, sizeof(struct sockaddr))< 0){
        exit(1);
    }
    stats->nb_packets_transmitted++;
    if_flood_print_point(opt);
    return;
}

static void if_flood_print_point(t_opt *opt){
    if(opt->quiet)
        return ;
    if (opt->flood)
        write(1,".",1);
}

static void if_verbose_copy_packet_for_print(bool verbose, t_conf *conf, char *packet){

    if (verbose)
        memcpy(conf->packet_sent, packet, PACKET_LEN);
}
