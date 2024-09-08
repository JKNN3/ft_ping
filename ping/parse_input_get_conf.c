#include "includes/ping.h"

static bool    get_dest_addr(char *addr, t_conf *conf);

bool    parse_input_get_conf(char *addr, t_conf *conf){
    if (!addr)
        return 0; // return usage
    if (!get_dest_addr(addr, conf))
        return 0;
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
    return 1;
}

bool init_conf_struct(t_conf *conf){
    conf->nb_packets_transmitted = 0;
    conf->id = getpid();
    return 0;
}