#include "includes/ping.h"

t_stats *get_stats(bool get, t_stats *stats_struct){
    static t_stats *stats_adress;

    if (get == TRUE)
        return (stats_adress);
    else{
        stats_adress = stats_struct;
        return NULL;
    }
}

int     get_sockfd(bool get, int fd){
    static int sockfd;

    if (get == TRUE)
        return sockfd;
    sockfd = fd;

    return 0;
}

bool puterr(char *error){
    write(2, error, strlen(error));
    return FALSE;
}

void puterr_and_exit(char *error, int exit_code){
    write(2, error, strlen(error));
    exit(exit_code);
}