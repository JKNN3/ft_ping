#include "includes/ping.h"

static void handle_signals(int sig);
static void print_sigquit_stats(t_stats *stats);

void intercept_and_handle_signals(){

    struct sigaction sa;
    sa.sa_handler = &handle_signals;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

static void handle_signals(int sig){
    t_stats *stats = get_stats(TRUE, NULL);

    if (sig == SIGQUIT)
        print_sigquit_stats(stats);
    else if (sig == SIGINT){
        print_stats_and_exit(stats, get_sockfd(1, 0), 0);
    }
}

static void print_sigquit_stats(t_stats *stats){

    printf("\b\b"); //  to get rid of the ctrl + \ (^\) hotkey print huuuuh
    fflush(stdout);

    PRINT_SIGQUIT_STATS( \
        stats->nb_packets_transmitted,  \
        stats->nb_packets_received,     \
        100 - ((stats->nb_packets_received / (stats->nb_packets_transmitted)) * 100), \
        stats->rtt_min,                 \
        compute_rtt_avg(stats),         \
        0.0,                            \
        stats->rtt_max                  \
    );
}