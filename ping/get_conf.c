#include "includes/ping.h"

static bool get_dest_addr(char *addr, t_conf *conf);
static bool init_conf_struct(t_conf *conf);
static void init_stats_struct(t_stats *stats);

bool    parse_input_get_conf(char *addr, t_conf *conf, t_stats *stats){
    if (!addr)
        return 0; // return usage
    if (!get_dest_addr(addr, conf))
        return 0;
    init_conf_struct(conf);
    init_stats_struct(stats);
    stats->dest_ip = inet_ntoa(conf->dest.sin_addr);
    get_stats(false, stats);
    get_sockfd(false, conf->sockfd);

    return 1;
}

static bool get_dest_addr(char *addr, t_conf *conf){

    struct addrinfo hints;
    struct addrinfo *res = NULL;

    memset(&conf->dest, 0, sizeof(struct sockaddr_in));
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_CANONNAME;

    conf->dest.sin_family = AF_INET;
    if (getaddrinfo(addr, NULL, &hints, &res)){
        freeaddrinfo(res);
        perror("getaddrinfo failed ");
        return 0;
    }

    conf->dest = *((struct sockaddr_in*)res->ai_addr);
    freeaddrinfo(res);
    return 1;
}

static bool init_conf_struct(t_conf *conf){
    conf->id = getpid();
    conf->exit_status = 0;
    conf->interval_time = 1;
    conf->seq = 0;

    return 0;
}

static void init_stats_struct(t_stats *stats){
    stats->dest_ip = NULL;
    stats->nb_packets_transmitted = 0;
    stats->nb_packets_received = 0;
    stats->loss_percentage = 0;
    stats->total_time_ms = 0;
    stats->rtt_min = FLT_MAX;
    stats->rtt_max = FLT_MIN;
    stats->rtt_sq_total = 0;
}
