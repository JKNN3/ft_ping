#include "includes/ping.h"

bool    parse_input_get_conf(char **argv, t_conf *conf, t_stats *stats, t_opt *opt){

    init_structs_and_singletons(conf, opt, stats);
    if (!regex_parse_input(argv, opt, conf))
        return FALSE; // return usage

    stats->dest_ip = inet_ntoa(conf->dest.sin_addr);
    return TRUE;
}


void resolve_dest_address(char *addr, t_conf *conf){

    struct addrinfo hints;
    struct addrinfo *res = NULL;

    memset(&conf->dest, 0, sizeof(struct sockaddr_in));
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_CANONNAME;

    conf->dest.sin_family = AF_INET;
    if (getaddrinfo(addr, NULL, &hints, &res)){
        freeaddrinfo(res);
        puterr_and_exit("ft_ping : unknown host\n", 1);
    }

    conf->dest = *((struct sockaddr_in*)res->ai_addr);
    freeaddrinfo(res);
}
