#include "includes/ping.h"

bool init_socket(t_conf *conf){
    
    conf->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (conf->sockfd < 0){
        perror("socket() failed ");
        return 0;
    }

    int opt_value = 1;
    if (setsockopt(conf->sockfd, IPPROTO_IP, IP_HDRINCL, &opt_value, sizeof(int)) != 0){
        perror("setsockopt IP_HDRINCL failed ");
        return 0;
    }

    int ttl = TIME_TO_LIVE;
    if (setsockopt(conf->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) != 0 ){
        perror("setsockopt IP_TTL failed ");
        return 0;
    }
    return 1;
}