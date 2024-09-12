# include "includes/ping.h"

static void init_conf_struct(t_conf *conf);
static void init_stats_struct(t_stats *stats);
static void init_opt_struct(t_opt *opt);

void    init_structs(t_conf *conf, t_opt *opt, t_stats *stats){

    init_conf_struct(conf);
    init_stats_struct(stats);
    init_opt_struct(opt);
}

static void init_conf_struct(t_conf *conf){
    conf->id = getpid();
    conf->exit_status = 0;
    conf->interval_time = 1;
    conf->seq = 0;
    conf->ttl = 64;
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

static void init_opt_struct(t_opt *opt){
    opt->audible = false;
    opt->count = false;
    opt->debug = false;
    opt->flood = false;
    opt->help = false;
    opt->print = false;
    opt->quiet = false;
    opt->usage = false;
    opt->verbose = false;
}