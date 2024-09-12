#include "includes/ping.h"

static void     print_final_stats(t_stats *stats);
static double   compute_rtt_avg(t_stats *stats);


void    print_stats_and_exit(t_stats *stats, int sockfd, int exit_status){

    print_final_stats(stats);
    close(sockfd);
    exit(exit_status);
}

void    print_core_dump_and_exit(int sockfd){
    write(2, "Quit (core dumped)\n", 20);
    close(sockfd);
    exit(131);
}

void print_sigquit_stats(t_stats *stats){

    printf("\b\b"); //  to get rid of the ctrl + \ (^\) hotkey print huuuuh
    fflush(stdout);

    PRINT_SIGQUIT_STATS( \
        stats->nb_packets_transmitted,  \
        stats->nb_packets_received,     \
        100 - ((stats->nb_packets_received / (stats->nb_packets_transmitted)) * 100), \
        stats->rtt_min,                 \
        compute_rtt_avg(stats),         \
        2.4,                            \
        stats->rtt_max                  \
    );
}

static void     print_final_stats(t_stats *stats){

    PRINT_FINAL_STATS(\
        stats->dest_ip,                                                               \
        stats->nb_packets_transmitted,                                                \
        stats->nb_packets_received,                                                   \
        100 - ((stats->nb_packets_received / (stats->nb_packets_transmitted)) * 100), \
        stats->rtt_min,                                                               \
        (stats->total_time_ms / stats->nb_packets_received),                          \
        stats->rtt_max,                                                               \
        compute_rtt_avg(stats));
}

static double   compute_rtt_avg(t_stats *stats){

    double average_rtt;
    double average_of_squared_rtt;
    double mdev;

    average_rtt = stats->total_time_ms / stats->nb_packets_received;
    average_of_squared_rtt = stats->rtt_sq_total / stats->nb_packets_received;
    mdev = sqrt((average_of_squared_rtt - (average_rtt * average_rtt)));
  
    return mdev;
}
