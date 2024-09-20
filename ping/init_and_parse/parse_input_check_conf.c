#include "../includes/ping.h"

static bool check_if_print_usage_or_help(t_opt *opt);
// static bool check_if_user_is_root(t_conf *conf);
static void check_if_missing_dest_ip(t_conf *conf);
static void check_flood_and_interval(t_conf *conf, t_opt *opt);

bool    parse_input_get_conf(char **argv, t_conf *conf, t_stats *stats, t_opt *opt){

    init_structs_and_singletons(conf, opt, stats);
    if (!regex_parse_input(argv, opt, conf))
        return FALSE;

    check_if_missing_dest_ip(conf);
    check_flood_and_interval(conf, opt);

    if (check_if_print_usage_or_help(opt))
        return FALSE;

    stats->dest_ip = inet_ntoa(conf->dest_addr.sin_addr);
    return TRUE;
}

static bool check_if_print_usage_or_help(t_opt *opt){
    if (opt->usage){
        PRINT_USAGE;
        return TRUE;
    }
    if (opt->help){
        PRINT_HELP;
        return TRUE;
    }
    return FALSE;
} 

static void check_if_missing_dest_ip(t_conf *conf){
    if (!conf->adress_resolved)
        puterr_and_exit(ERROR_MISSING_HOST_OPERAND, 64);
}

static void check_flood_and_interval(t_conf *conf, t_opt *opt){
    if (opt->flood && opt->interval)
        puterr_and_exit(ERROR_INTERVAL_AND_FLOOD_INCOMPATIBLE, 1);
    if (opt->flood)
        conf->interval_time = 0;
}
