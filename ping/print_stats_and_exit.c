#include "includes/ping.h"

void    print_stats_and_exit(t_stats *stats, t_conf *conf){

    print_final_stats(stats, conf);
    close(conf->sockfd);
    exit(conf->exit_status);
}


static void     print_final_stats(t_stats *stats, t_conf *conf){

    PRINT_FINAL_STATS(conf->dest_ip,                                                                 \
                      conf->nb_packets_transmitted-1,                                                \
                      stats->nb_packets_received,                                                    \
                      100 - ((stats->nb_packets_received / (conf->nb_packets_transmitted-1)) * 100),  \
                      stats->total_time_ms,                                                          \
                      stats->rtt_min,                                                               \
                      (stats->total_time_ms / stats->nb_packets_received),                            \
                      stats->rtt_max,                                                               \
                      compute_rtt_avg(&stats));
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