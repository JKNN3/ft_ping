#include "ping.h"

bool puterr(char *error){

    write(2, error, strlen(error));
    return FALSE;
}

void puterr_and_exit(int err, int exit_code){

    t_stats *stats = get_stats(GET, NULL);
    (void)err;
    if (stats->dest_name)
        free(stats->dest_name);
    if (get_timeout_status(GET))
        pthread_cancel(*get_thread());
    int *fds = get_sockfds(GET, 0, 0);
    close(fds[0]);
    close(fds[1]);
    exit(exit_code);
}

void    print_header(t_opt *opt, t_conf *conf, t_stats *stats){

    if (!opt->verbose){
        PRINT_HEADER_MSG(stats->dest_name, stats->dest_ip, DATA_BYTES);
        return;
    }
    PRINT_HEADER_MSG_VERBOSE(stats->dest_name, stats->dest_ip, DATA_BYTES, conf->id)
}

bool check_count_option(t_conf *conf){

    if (conf->nb_packets_to_send != 0 && conf->nb_packets_to_send == (unsigned long long)conf->seq)
        return FALSE;
    return TRUE;
}

t_stats *get_stats(bool request, t_stats *stats_struct){

    static t_stats *stats_adress = NULL;

    if (request == GET)
        return (stats_adress);
    else{
        stats_adress = stats_struct;
        return NULL;
    }
}
