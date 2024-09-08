#ifndef PING_H
# define PING_H

# include <stdio.h>                 // printf
# include <string.h>                // memset()
# include <regex.h> 
# include <unistd.h>                // write()
# include <sys/types.h> 
# include <sys/socket.h>    
# include <netdb.h>                 // socket(), getaddrinfo()
# include <netinet/in.h>    
# include <netinet/ip.h>            // struct ip
# include <netinet/ip_icmp.h>       // struct icmp
# include <arpa/inet.h>             // inet_ntop()
# include <sys/time.h>              // gettimeofday()
# include <errno.h>
# include "macros.h"
# include "regex.h"
# include <sys/ioctl.h>             // ioctl() and ifreq struct
# include <net/if.h>                // IFNAMSIZ constant
# include <stdlib.h>                // malloc
# include <stdbool.h>               // TRUE, FALSE 

typedef struct  s_conf  {
    int                     sockfd;
    struct sockaddr_in      dest;
    unsigned short          nb_packets_transmitted;
    struct timeval          start_timestamp;
    pid_t                   id;
    
}               t_conf ; 

typedef struct  s_stats{
    unsigned int            nb_packets_transmitted;
    unsigned int            nb_packets_received;
    double                  loss_percentage;
    unsigned long int       total_time_ms;
//      rtt = round_trip delay
    float                   rtt_min;        // min : conf->rtt_min > rtt ? rtt : conf->rtt_min
    float                   rtt_total;      //  avg = total / nb_packets_received
    float                   rtt_max;        // min : conf->rtt_max < rtt ? rtt : conf->rtt_max
    float                   rtt_sq_total;   //  += rtt * rtt;
}               t_stats;


/*          parse_argv_get_conf.c   */
bool    parse_input_get_conf(char *addr, t_conf *conf);

/*          print_packet.c          */
void    print_packet(char *packet);

/*          socket.c                */
bool init_socket(t_conf *conf);


/*          fill_packet.c           */
void    fill_ip_header(struct ip *ip_header,t_conf *conf);
void    fill_icmp_msg(struct icmp *icmp_message, t_conf *conf);
void    fill_payload(char *packet);

/*          compute_checksum.c      */
short   compute_checksum(void *packet, int len); // len = longueur du packet en octets/bytes

/*          send_ping.c             */
void send_ping(t_conf *conf);


#endif