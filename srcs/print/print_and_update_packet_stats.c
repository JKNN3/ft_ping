#include "../../includes/ping.h"

static void     update_stats(t_stats *stats, double rtt);
static double   compute_elapsed_time(struct timeval *start);

void print_and_update_packet_stats( t_stats *stats, char *packet, int ret, t_opt *opt){

    unsigned short  seq = 0;
    int             ttl = 0;
    double          time_elapsed = 0.0;

    time_elapsed = compute_elapsed_time((void*)&(packet[IP_HEADER_LEN + ICMP_HEADER_LEN]));
    update_stats(stats, time_elapsed);
    
    if (opt->quiet) return;
    if (opt->flood){
        write(1,"\b",1);
        return;
    }
    seq = ntohs(((struct icmp *)(&packet[IP_HEADER_LEN]))->icmp_seq);
    ttl = ((struct ip *)(packet))->ip_ttl;
    PRINT_PACKET_STATS(ret - IP_HEADER_LEN, stats->dest_ip, seq, ttl, time_elapsed);
};

static double   compute_elapsed_time(struct timeval *start){

    struct timeval	end;
    double          time_elapsed = 0.0;

    memset(&end, 0, sizeof(struct timeval));
	gettimeofday(&end, NULL);
    time_elapsed =  ((double)((double)end.tv_sec - (double)start->tv_sec) * 1000) +\
		            (double)((double)end.tv_usec - (double)start->tv_usec) / 1000;

	return (time_elapsed);
}

static void     update_stats(t_stats *stats, double rtt){

    stats->total_time_ms += rtt;
    stats->nb_packets_received++;
    stats->rtt_sq_total += rtt*rtt;
    stats->rtt_min = MIN(stats->rtt_min, rtt);
    stats->rtt_max = MAX(stats->rtt_max, rtt);
}