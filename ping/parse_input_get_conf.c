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
    return 1;
}



static bool get_dest_addr(char *addr, t_conf *conf){

    struct addrinfo hints;
    struct addrinfo *res = NULL;

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

    conf->dest_ip = inet_ntoa(conf->dest.sin_addr);
    return 1;
}


static void init_stats_struct(t_stats *stats){
    stats->nb_packets_received = 0;
    stats->total_time_ms = 0;
    stats->rtt_sq_total = 0;
    stats->rtt_min = FLT_MAX;
    stats->rtt_max = FLT_MIN;
}

static bool init_conf_struct(t_conf *conf){
    conf->nb_packets_transmitted = 1;
    conf->id = getpid();
    conf->exit_status = 0;
    conf->interval_time = 1;
    return 0;
}