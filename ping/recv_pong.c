#include "includes/ping.h"

static int  receive_packet(t_conf *conf, char *packet_recv);
static bool check_packet_received(char *packet, int bytes_recv, t_opt *opt, t_conf *conf);
static bool check_id(char *packet, t_conf *conf);

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

bool recv_pong(t_conf *conf, t_stats *stats, t_opt *opt){

    static char     packet_recv[PACKET_LEN];

        memset(packet_recv, 0, PACKET_LEN);

        while(TRUE){

            int bytes_recv = receive_packet(conf, packet_recv);
            if (bytes_recv < 0){
                printf("timeout\n");
                return FALSE;
            }
            // if (opt->audible)
            //     printf("\a");
            printf("bytes reçus: %d\n", bytes_recv);
            if (check_packet_received(packet_recv, bytes_recv, opt, conf))
                print_and_update_packet_stats(stats, packet_recv, bytes_recv, opt);
            return TRUE;
        }
    return TRUE;
}

static int receive_packet(t_conf *conf, char *packet_recv){

    // socklen_t       addrlen;
    memset(packet_recv, 0, PACKET_LEN);

    int bytes_recv = recv(conf->sockfd, packet_recv, PACKET_LEN, 0);

    return (bytes_recv);
}

static bool check_packet_received(char *packet, int bytes_recv, t_opt *opt, t_conf *conf){

    int type = (int)((struct icmp *)(&packet[IP_HEADER_LEN]))->icmp_type;
    // unsigned short id_icmp = ((struct icmp *)(&packet[IP_HEADER_LEN]))->icmp_id;
 
    if (type != ICMP_ECHOREPLY){
        if (type == ICMP_ECHO)
            return FALSE;
    
        if (!check_id(packet, conf))
            return FALSE;
        char *destination = inet_ntoa((struct in_addr)(((struct ip*)(packet))->ip_dst));
        PRINT_PACKET_ERR(bytes_recv - IP_HEADER_LEN, destination, icmp_errors[type]);
        if (opt->verbose)
            print_packet_sent_dump(conf->packet_sent, inet_ntoa(*(struct in_addr *)&(((struct ip*)packet)->ip_dst)));
        return FALSE;
    }
    return TRUE;
}

static bool check_id(char *packet, t_conf *conf){
    if (ntohs((int)((struct ip*)&packet[48])->ip_id) != (conf->id & 0xFFFF))
        return FALSE;
    return TRUE;
}
