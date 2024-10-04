#include "ping.h"

static void init_conf_struct(t_conf *conf);
static void init_stats_struct(t_stats *stats);
static void init_opt_struct(t_opt *opt);

void    init_structs(t_conf *conf, t_opt *opt, t_stats *stats){

    init_conf_struct(conf);
    init_stats_struct(stats);
    init_opt_struct(opt);

    get_stats(false, stats);
}

static void init_conf_struct(t_conf *conf){

    conf->id = getpid();
    conf->interval_time = 1;
    conf->seq = 0;
    conf->ttl = 64;
    conf->adress_resolved = false;
    memset(conf->packet_sent, 0, PACKET_LEN);
}

static void init_stats_struct(t_stats *stats){

    memset(stats, 0, sizeof(t_stats));
    stats->rtt_min = FLT_MAX;
    stats->rtt_max = FLT_MIN;
}

static void init_opt_struct(t_opt *opt){

    memset(opt, 0, sizeof(t_opt));
}

