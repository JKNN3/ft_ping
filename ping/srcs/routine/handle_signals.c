#include "../../includes/ping.h"

static void handle_signals(int sig);

static void handle_signals(int sig){
    t_stats *stats = get_stats(TRUE, NULL);

    if (sig == SIGQUIT){        // inetutils coredump and the iputils print stats so
        if(stats->nb_packets_transmitted % 2 == 0){
            print_sigquit_stats(stats);
            return;
        }
        puterr_and_exit(ERROR_CORE_DUMP, 131);
        return;
    }
    print_final_stats_and_exit(stats, 0);
}

// handle <ctrl + c> and <ctrl + \> hotkeys signals
void intercept_and_handle_signals(){

    static struct sigaction sa;
    sa.sa_handler = &handle_signals;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}
