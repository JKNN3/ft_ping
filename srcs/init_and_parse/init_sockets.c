#include "../../includes/ping.h"

static bool init_sock_send(t_opt *opt, t_conf *conf);
static bool init_sock_recv(t_conf *conf);

bool init_sockets(t_opt *opt, t_conf *conf){
    
    if (!init_sock_send(opt, conf))
        return FALSE;
    if (!init_sock_recv(conf))
        return FALSE;

    get_sockfds(false, conf->sockfd_send, conf->sockfd_recv);
    return TRUE;
}

static bool init_sock_send(t_opt *opt, t_conf *conf){

    conf->sockfd_send = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (conf->sockfd_send < 0){
        perror("socket() for receiving socket failed ");
        return FALSE;
    }

    int opt_value = 1;
    if (setsockopt(conf->sockfd_send, IPPROTO_IP, IP_HDRINCL, &opt_value, sizeof(int)) != 0){
        perror("setsockopt IP_HDRINCL failed ");
        return FALSE;
    }

    int ttl = conf->ttl;
    if (setsockopt(conf->sockfd_send, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) != 0 ){
        perror("setsockopt IP_TTL failed ");
        return FALSE;
    }
    int on = 1;
    if (opt->debug){
        if (setsockopt(conf->sockfd_send, SOL_SOCKET, SO_DEBUG, (char *)&on, sizeof(on)) != 0 ){
            perror("setsockopt SO_DEBUG failed ");
            return FALSE;
        }
    }
    return TRUE;
}

static bool init_sock_recv(t_conf *conf){

    conf->sockfd_recv = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (conf->sockfd_recv < 0){
        perror("socket() for sending socket failed ");
        return FALSE;
    }

    struct timeval timeout;      
    timeout.tv_sec = 4;
    timeout.tv_usec = 0;
    
    if (setsockopt (conf->sockfd_recv, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof timeout) < 0){
        perror("setsockopt SO_RCVTIMEO failed ");
        return FALSE;
    }
    return TRUE;
}


int     *get_sockfds(bool request, int send_fd, int recv_fd){
    
    static int sockfd[2] = {0, 0};

    if (request == GET)
        return (int *)&sockfd;
    sockfd[0] = send_fd;
    sockfd[1] = recv_fd;
    return 0;
}
