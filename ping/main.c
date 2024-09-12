#include "includes/ping.h"

/*
          TO DO

    - faire des tests avec tinytest :v

          TO DO NEXT
    - gestion d'erreurs
    - check du packet reçu huu

  ~ maybe find a way to make valgrind work

*/
# include <math.h>


int main(int argc, char **argv){
    t_conf  conf;
    t_stats stats;
    t_opt   opt;

    if (!parse_input_get_conf(argv, &conf, &stats, &opt) || !init_socket(&conf))
        return 0;

    PRINT_HEADER_MSG(stats.dest_ip, 1);

    while(1){

        intercept_and_handle_signals();
        send_ping(&conf);
        recv_pong(&conf, &stats);

        sleep(conf.interval_time);
    }
    print_stats_and_exit(&stats, conf.sockfd, conf.exit_status);
}
