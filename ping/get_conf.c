#include "includes/ping.h"

static bool get_dest_addr(char *addr, t_conf *conf);

bool    parse_input_get_conf(char **argv, t_conf *conf, t_stats *stats, t_opt *opt){

    init_structs(conf, opt, stats);

    if (!regex_parse_input(argv, opt, conf))
        return FALSE; // return usage
    if (!get_dest_addr(conf->dest_name_or_ip, conf))
        return FALSE;
    stats->dest_ip = inet_ntoa(conf->dest.sin_addr);
    get_stats(false, stats);
    get_sockfd(false, conf->sockfd);

    return TRUE;
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
        perror("getaddrinfo failed ");
        freeaddrinfo(res);
        return FALSE;
    }

    conf->dest = *((struct sockaddr_in*)res->ai_addr);
    freeaddrinfo(res);
    return TRUE;
}
