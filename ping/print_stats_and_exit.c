#include "includes/ping.h"

static void     print_final_stats(t_stats *stats);


void    print_stats_and_exit(t_stats *stats, int sockfd, int exit_status){

    print_final_stats(stats);
    close(sockfd);
    exit(exit_status);
}


static void     print_final_stats(t_stats *stats){

    PRINT_FINAL_STATS(\
        stats->dest_ip,                                                               \
        stats->nb_packets_transmitted,                                                \
        stats->nb_packets_received,                                                   \
        100 - ((stats->nb_packets_received / (stats->nb_packets_transmitted)) * 100), \
        stats->total_time_ms,                                                         \
        stats->rtt_min,                                                               \
        (stats->total_time_ms / stats->nb_packets_received),                          \
        stats->rtt_max,                                                               \
        compute_rtt_avg(stats));
}

double   compute_rtt_avg(t_stats *stats){

    double average_rtt;
    double average_of_squared_rtt;
    double mdev;

    average_rtt = stats->total_time_ms / stats->nb_packets_received;
    average_of_squared_rtt = stats->rtt_sq_total / stats->nb_packets_received;
    mdev = sqrt((average_of_squared_rtt - (average_rtt * average_rtt)));
  
    return mdev;
}