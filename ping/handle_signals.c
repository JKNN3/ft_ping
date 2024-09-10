#include "includes/ping.h"

static void handle_signals(int sig){
    if (sig == SIGQUIT)
        printf("sigquit\n");
    elif (sig == SIGINT)
        printf("sigint\n");

}

void intercept_and_handle_signals(){

    struct sigaction sa;
    sa.sa_handler = &handle_signals;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGSTOP, &sa, NULL);
}