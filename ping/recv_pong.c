#include "includes/ping.h"

static double  compute_elapsed_time(struct timeval *start, struct timeval *end);
static void update_stats(t_stats *stats, double rtt);

int recv_pong(t_conf *conf, t_stats *stats){
    static char     packet_recv[84];
    unsigned short  seq = 0;
	struct timeval	time;
    int             ttl = 0;
    double          time_elapsed = 0.0;

    memset(&time, 0, sizeof(struct timeval));
    memset(&packet_recv, 0, PACKET_LEN);

    int ret = recv(conf->sockfd, packet_recv, PACKET_LEN, 0);

    seq = ((struct icmp *)(&packet_recv[IP_HEADER_LEN]))->icmp_seq;
    int type = ((struct icmp *)(&packet_recv[IP_HEADER_LEN]))->icmp_type;
    printf("type : %d\n", type);
    ttl = ((struct ip *)(packet_recv))->ip_ttl;
	gettimeofday(&time, NULL);
    time_elapsed = compute_elapsed_time((void*)&(packet_recv[IP_HEADER_LEN + ICMP_HEADER_LEN]), &time);

    PRINT_PACKET_STATS(ret - IP_HEADER_LEN, stats->dest_ip, seq, ttl, time_elapsed);
    update_stats(stats, time_elapsed);
    return 0;
}

static void check_packet(){

    // u_int16_t		recvd_seq = ntohs(icmp->un.echo.sequence);
}

static void update_stats(t_stats *stats, double rtt){
    stats->total_time_ms += rtt;
    stats->nb_packets_received++;
    stats->rtt_sq_total += rtt*rtt;
    stats->rtt_min = MIN(stats->rtt_min, rtt);
    stats->rtt_max = MAX(stats->rtt_max, rtt);
}

static double  compute_elapsed_time(struct timeval *start, struct timeval *end){
	return (((double)((double)end->tv_sec - (double)start->tv_sec) * 1000) +
		(double)((double)end->tv_usec - (double)start->tv_usec) / 1000);
}

static const char	*icmp_responses[] =
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