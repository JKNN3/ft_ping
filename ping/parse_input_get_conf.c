#include "includes/ping.h"

static bool check_if_print_usage_or_help(t_opt *opt);
static bool check_if_user_is_root(t_conf *conf);

bool    parse_input_get_conf(char **argv, t_conf *conf, t_stats *stats, t_opt *opt){

    init_structs_and_singletons(conf, opt, stats);
    if (!regex_parse_input(argv, opt, conf))
        return FALSE; // return usage

    if (check_if_print_usage_or_help(opt))
        return FALSE;
    if (opt->flood)
        check_if_user_is_root(conf);
    stats->dest_ip = inet_ntoa(conf->dest.sin_addr);
    return TRUE;
}


void resolve_dest_address(char *addr, t_conf *conf){
    if (conf->dest_name_or_ip != NULL) return;

    struct addrinfo hints;
    struct addrinfo *res = NULL;

    memset(&conf->dest, 0, sizeof(struct sockaddr_in));
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_CANONNAME;

    conf->dest.sin_family = AF_INET;
    if (getaddrinfo(addr, NULL, &hints, &res)){
        freeaddrinfo(res);
        puterr_and_exit(ERROR_UNKNOWN_HOST, 1);
    }

    conf->dest_name_or_ip = addr;
    conf->dest = *((struct sockaddr_in*)res->ai_addr);
    freeaddrinfo(res);
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

static bool check_if_user_is_root(t_conf *conf){
    char *user = NULL;

    user = getenv("USER");
    if (strcmp(user, "root") == 0){
        conf->interval_time = 0;
        return TRUE;
    }
    puterr_and_exit(ERROR_NEED_TO_BE_ROOT, 0); // essayer de voir plus tard siy'a un truc avec jsp temporaire pcq jsp
    return FALSE;
}