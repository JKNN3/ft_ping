#include "includes/ping.h"

static void handle_signals(int sig);

// handle <ctrl + c> and <ctrl + \> hotkeys signals
void intercept_and_handle_signals(){

    struct sigaction sa;
    sa.sa_handler = &handle_signals;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

static void handle_signals(int sig){
    t_stats *stats = get_stats(TRUE, NULL);

    if (sig == SIGQUIT){        // inetutils coredump and the iputils print stats so
        if(stats->nb_packets_transmitted % 2 == 0) // % 0 ??? :clown:
            print_sigquit_stats(stats);
        else
            print_core_dump_and_exit(get_sockfd(1, 0));
    }
    else if (sig == SIGINT){
        print_stats_and_exit(stats, get_sockfd(1, 0), 0);
    }
}
