#include "../../includes/ping.h"

bool init_socket(t_opt *opt, t_conf *conf){
    
    conf->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (conf->sockfd < 0){
        perror("socket() failed ");
        return FALSE;
    }
    struct timeval timeout;      
    timeout.tv_sec = 4;
    timeout.tv_usec = 0;
    
    if (setsockopt (conf->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof timeout) < 0){
        perror("setsockopt SO_RCVTIMEO failed ");
        return FALSE;
    }
    int opt_value = 1;
    if (setsockopt(conf->sockfd, IPPROTO_IP, IP_HDRINCL, &opt_value, sizeof(int)) != 0){
        perror("setsockopt IP_HDRINCL failed ");
        return FALSE;
    }

    int ttl = conf->ttl;
    if (setsockopt(conf->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) != 0 ){
        perror("setsockopt IP_TTL failed ");
        return FALSE;
    }
    int on = 1;
    if (opt->debug){
        if (setsockopt(conf->sockfd, SOL_SOCKET, SO_DEBUG, (char *)&on, sizeof(on)) != 0 ){
            perror("setsockopt SO_DEBUG failed ");
            return FALSE;
        }
    }

    get_sockfd(false, conf->sockfd);
    return TRUE;
}

int     get_sockfd(bool request, int fd){
    
    static int sockfd = 0;

    if (request == GET)
        return sockfd;
    sockfd = fd;

    return 0;
}
