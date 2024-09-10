#include "includes/ping.h"

t_stats *get_stats(bool get, t_stats *stats_struct){
    static t_stats *stats_adress;

    if (get == true)
        return (stats_adress);
    else{
        stats_adress = stats_struct;
        return NULL;
    }
}

int     get_sockfd(bool get, int fd){
    static int sockfd;

    if (get == true)
        return sockfd;
    sockfd = fd;

    return 0;
}