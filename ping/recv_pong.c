#include "includes/ping.h"

static const char	*icmp_errors[] =
{
	[ICMP_DEST_UNREACH]		= "Destination Unreachable",
	[ICMP_SOURCE_QUENCH]	= "Source Quench",
	[ICMP_REDIRECT]			= "Redirect (change route)",
	[ICMP_ECHO]				= "Echo Request",
	[ICMP_TIME_EXCEEDED]	= "Time to live exceeded",
	[ICMP_PARAMETERPROB]	= "Parameter Problem",
	[ICMP_TIMESTAMP]		= "Timestamp Request",
	[ICMP_TIMESTAMPREPLY]	= "Timestamp Reply",
	[ICMP_INFO_REQUEST]		= "Information Request",
	[ICMP_INFO_REPLY]		= "Information Reply",
	[ICMP_ADDRESS]			= "Address Mask Request",
	[ICMP_ADDRESSREPLY]		= "Address Mask Reply"
};

static bool     check_packet_receveid(char *packet_recv, int bytes_recv, t_stats *stats);
static void     print_packet_stats_update_stats( t_stats *stats, char *packet_recv, int ret);
static double   compute_elapsed_time(struct timeval *start);
static void     update_stats(t_stats *stats, double rtt);

int recv_pong(t_conf *conf, t_stats *stats){

    static char     packet_recv[84];

    memset(&packet_recv, 0, PACKET_LEN);
    int ret = recv(conf->sockfd, packet_recv, PACKET_LEN, 0);

    if (!check_packet_receveid(packet_recv, ret, stats)){
        return FALSE;
    }
    print_packet_stats_update_stats(stats, packet_recv, ret);
    return 0;
}

static bool check_packet_receveid(char *packet_recv, int bytes_recv, t_stats *stats){
    int type = ((struct icmp *)(&packet_recv[IP_HEADER_LEN]))->icmp_type;

    if (type > 0){
        PRINT_PACKET_ERR(bytes_recv - IP_HEADER_LEN, stats->dest_ip, icmp_errors[type]);
        return FALSE;
    }
    return TRUE;
}

static void     print_packet_stats_update_stats( t_stats *stats, char *packet_recv, int ret){
    unsigned short  seq = 0;
    int             ttl = 0;
    double          time_elapsed = 0.0;

    seq = ((struct icmp *)(&packet_recv[IP_HEADER_LEN]))->icmp_seq;
    ttl = ((struct ip *)(packet_recv))->ip_ttl;
    time_elapsed = compute_elapsed_time((void*)&(packet_recv[IP_HEADER_LEN + ICMP_HEADER_LEN]));

    PRINT_PACKET_STATS(ret - IP_HEADER_LEN, stats->dest_ip, seq, ttl, time_elapsed);
    update_stats(stats, time_elapsed);
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