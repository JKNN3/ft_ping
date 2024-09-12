#ifndef PING_H
# define PING_H

# include "macros.h"
# include "regex_macros.h"
# include "print_macros.h"

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
# include <sys/ioctl.h>             // ioctl() and ifreq struct
# include <net/if.h>                // IFNAMSIZ constant
# include <stdlib.h>                // malloc
# include <stdbool.h>               // TRUE, FALSE 
# include <float.h>                 // FLT_MAX, FLT_MIN
# include <math.h>                 // sqrt()
# include <signal.h>                // sigaction
# include <curses.h> 

typedef struct  s_conf  {
    int                     sockfd;
    pid_t                   id;
    int                     exit_status;
    long double             interval_time;      //in seconds
    int                     seq;
    struct sockaddr_in      dest;
    struct timeval          start_timestamp;
    char                    *dest_name_or_ip;
    unsigned long long int  nb_packets_to_send;
    int                     ttl;
}               t_conf ; 

typedef struct option{
    bool                audible;    // -a
    bool                debug;      // -d, --debug
    bool                count;
    bool                flood;      // -f --flood
    bool                help;       // -? --help
    bool                print;      // --print
    bool                quiet;      // -q, --quiet 
    bool                usage;      // --usage
    bool                verbose;    // -v --verbose

//    unsigned long int   count;      // -c --count=nb
//    double              interval;   // -i --interval=nb 
//    unsigned long int   timeout;    // -w, --timeout=N
//    int                 ttl;        // --ttl
}               t_opt ;


typedef struct  s_stats{
    char*                   dest_ip;
    unsigned short          nb_packets_transmitted;
    unsigned int            nb_packets_received;
    double                  loss_percentage;
    long double             total_time_ms;
//      rtt = round_trip delay
    float                   rtt_min;
    float                   rtt_max;
    long double             rtt_sq_total;
}               t_stats;


/*          parse_argv_get_conf.c   */
bool    parse_input_get_conf(char **argv, t_conf *conf, t_stats *stats, t_opt *opt);

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

/*          recv_pong.c             */
int recv_pong(t_conf *conf, t_stats *stats);

/*          print_stats_and_exit.c  */
void    print_stats_and_exit(t_stats *stats, int sockfd, int exit_status);
double   compute_rtt_avg(t_stats *stats);

/*          handle_signals.c        */
void    intercept_and_handle_signals();

/*          utils.c                 */
t_stats *get_stats(bool get, t_stats *stats_struct);
int     get_sockfd(bool get, int fd);
bool    puterr(char *error);

bool regex_parse_input(char ** argv, t_opt *opt, t_conf *conf);
bool regex_check_format(const char *testedStr, const char *regex);

/*          init_structs.c          */
void    init_structs(t_conf *conf, t_opt *opt, t_stats *stats);

#endif