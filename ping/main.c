#include "includes/ping.h"

/*
          TO DO

    - parsing
    - compute and print statistics
    - faire une boucle ou on check le tpsnintervalle d'envoi
    - gérer les signaux
    - booléen a mettre a 0 si on revoit un signal

          TO DO NEXT

    - recv (need parsing too)

  ~ maybe find a way to make valgrind work

*/
# include <math.h>


int main(int argc, char **argv){
    t_conf  conf;
    t_stats stats;
    if (!parse_input_get_conf(argv[1], &conf, &stats) || !init_socket(&conf))
        return 0;

    PRINT_HEADER_MSG(stats.dest_ip, 1);

    while(1){

        intercept_and_handle_signals();
        send_ping(&conf);
        recv_pong(&conf, &stats);

        usleep(1000000);
    }
    print_stats_and_exit(&stats, conf.sockfd, conf.exit_status);
}
