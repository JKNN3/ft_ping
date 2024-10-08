#ifndef PING_H
# define PING_H

# include "macros.h"
# include "regex_macros.h"
# include "print_macros.h"
# include "errors.h"

# include <stdio.h>                 // printf(), sprintf(), fprintf()
# include <string.h>                // memset(), memcpy()
# include <regex.h>                 // regex_t, regcomp(), regexec(), regmatch(), regfree()
# include <unistd.h>                // write()
# include <sys/types.h> 
# include <sys/socket.h>    
# include <netdb.h>                 // socket(), getaddrinfo()
# include <netinet/in.h>    
# include <netinet/ip.h>            // struct ip
# include <netinet/ip_icmp.h>       // struct icmp
# include <arpa/inet.h>             // inet_ntop()
# include <sys/time.h>              // gettimeofday()
# include <errno.h>                 // perror()
# include <sys/ioctl.h>             // ioctl() and ifreq struct
# include <stdlib.h>                // malloc()
# include <stdbool.h>               // bool, TRUE, FALSE 
# include <float.h>                 // FLT_MAX, FLT_MIN
# include <math.h>                  // sqrt()
# include <signal.h>                // sigaction, kill()
# include <pthread.h>               // pthread_t, pthread_create()


typedef struct  s_conf  {
    int                     sockfd;
    int                     sockfd_send;
    int                     sockfd_recv;
    pid_t                   id;
    long double             interval_time;
    unsigned long int       timeout;
    unsigned long int       seq;
    struct sockaddr_in      dest_addr;
    struct timeval          start_timestamp;
    bool                    adress_resolved;
    unsigned long long int  nb_packets_to_send;
    int                     ttl;
    char                    packet_sent[PACKET_LEN];
}               t_conf ; 

typedef struct option{
    bool                audible;
    bool                debug;
    bool                flood;
    bool                quiet;
    bool                usage;
    bool                verbose;
    bool                help;
    bool                timeout;
    bool                count;
    bool                interval;
}               t_opt ;


typedef struct  s_stats{
    char                    *dest_ip;
    char                    *dest_name;
    unsigned int            nb_packets_transmitted;
    unsigned int            nb_packets_received;
    double                  loss_percentage;
    long double             total_time_ms;
    unsigned int            nb_error;
    float                   rtt_min;
    float                   rtt_max;
    long double             rtt_sq_total;
}               t_stats;


/*** init_and_parse ***/

bool        parse_input_check_conf(char **argv, t_conf *conf, t_stats *stats, t_opt *opt);
                // parse_input_check_conf.c

bool        regex_parse_input(char ** argv, t_opt *opt, t_conf *conf);
                // regex_parse_input.c

void        init_structs(t_conf *conf, t_opt *opt, t_stats *stats);
                // init_structs.c

bool        init_sockets(t_opt *opt, t_conf *conf);
int         *get_sockfds(bool request, int send_fd, int recv_fd);
                // init_sockets.c


/*** print ***/

void        print_packet_sent_dump(char *packet_sent, char *src_ip);
                // print_packet_sent_dump.c

void        print_final_stats_and_exit(t_stats *stats, int exit_status);
void        print_core_dump_and_exit();
void        print_sigquit_stats(t_stats *stats);
                // print_final_stats_and_exit.c

void        print_and_update_packet_stats( t_stats *stats, char *packet, int ret, t_opt *opt);
                // print_and_update_packet_stats.c

/*** routine ***/

void        fill_packet(char *packet, t_conf *conf);
                // fill_packet.c

short       compute_checksum(void *packet, int len);
                // compute_checksum.c
            
void        send_ping(t_conf *conf, t_stats *stats, t_opt *opt);
                // send_ping.c

bool        recv_pong(t_conf *conf, t_stats *stats, t_opt *opt);
                // recv_pong.c

void        intercept_and_handle_signals();
                // handle_signals.c

void        create_thread_if_timeout(t_opt *opt, t_conf *conf);
bool        get_timeout_status(bool request);
pthread_t * get_thread();
                // create_thread_if_timeout.c

bool        puterr(char *error);
void        puterr_and_exit(int err, int exit_code);
void        print_header(t_opt *opt, t_conf *conf, t_stats *stats);
bool        check_count_option(t_conf *conf);
t_stats *   get_stats(bool request, t_stats *stats_struct);
                // utils.c 




#endif