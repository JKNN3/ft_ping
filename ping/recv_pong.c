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

static bool     check_packet_received(char *packet, int bytes_recv, t_stats *stats, t_opt *opt);
static void     print_and_update_stats( t_stats *stats, char *packet, int ret, t_opt *opt);
static double   compute_elapsed_time(struct timeval *start);
static void     update_stats(t_stats *stats, double rtt);

bool recv_pong(t_conf *conf, t_stats *stats, t_opt *opt){

    static char     packet_recv[84];

    memset(&packet_recv, 0, PACKET_LEN);
    int ret = recv(conf->sockfd, packet_recv, PACKET_LEN, 0);
    if (!check_packet_received(packet_recv, ret, stats, opt))
        return FALSE;
    // if (opt->audible)
    //     printf("\a");
    print_and_update_stats(stats, packet_recv, ret, opt);
    return TRUE;
}

static bool check_packet_received(char *packet, int bytes_recv, t_stats *stats, t_opt *opt){

    int type = ((struct icmp *)(&packet[IP_HEADER_LEN]))->icmp_type;

    if (type > 0){
        PRINT_PACKET_ERR(bytes_recv - IP_HEADER_LEN, stats->dest_ip, icmp_errors[type]);
        if (opt->verbose)
            print_packet_dump(packet);
        return FALSE;
    }
    return TRUE;
}

static void print_and_update_stats( t_stats *stats, char *packet, int ret, t_opt *opt){

    unsigned short  seq = 0;
    int             ttl = 0;
    double          time_elapsed = 0.0;

    seq = ((struct icmp *)(&packet[IP_HEADER_LEN]))->icmp_seq;
    ttl = ((struct ip *)(packet))->ip_ttl;
    time_elapsed = compute_elapsed_time((void*)&(packet[IP_HEADER_LEN + ICMP_HEADER_LEN]));
    if (!opt->quiet && !opt->flood)
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