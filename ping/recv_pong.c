#include "includes/ping.h"

static double  calculate_elapsed_time(struct timeval *start, struct timeval *end);
static void update_stats(t_stats *stats, double rtt);

int recv_pong(t_conf *conf, t_stats *stats){
    static char packet_recv[84];

    memset(&packet_recv, 0, PACKET_LEN);
    int ret = recv(conf->sockfd, packet_recv, PACKET_LEN, 0);

    unsigned short  seq;
	struct timeval	time;
    int             ttl;
    double          time_elapsed;

    seq = ((struct icmp *)(&packet_recv[IP_HEADER_LEN]))->icmp_seq;
    ttl = ((struct ip *)(packet_recv))->ip_ttl;
	gettimeofday(&time, NULL);
    time_elapsed = calculate_elapsed_time((void*)&(packet_recv[IP_HEADER_LEN + ICMP_HEADER_LEN]), &time);

    PRINT_PACKET_STATS(conf->dest_ip, seq, ttl, time_elapsed);
    update_stats(stats, time_elapsed);
    return 0;
}

static void update_stats(t_stats *stats, double rtt){
    stats->total_time_ms += rtt;
    stats->nb_packets_received++;
    stats->rtt_sq_total += rtt*rtt;
    stats->rtt_min = MIN(stats->rtt_min, rtt);
    stats->rtt_max = MAX(stats->rtt_max, rtt);
}

static double  calculate_elapsed_time(struct timeval *start, struct timeval *end){
	return (((double)((double)end->tv_sec - (double)start->tv_sec) * 1000) +
		(double)((double)end->tv_usec - (double)start->tv_usec) / 1000);
}