#include "includes/ping.h"

/*
          TO DO

    - faire des tests avec tinytest :v
    - compute stddev

          TO DO NEXT
    - gestion d'erreurs
    - check du packet reçu huu

  ~ maybe find a way to make valgrind work URGH

*/
# include <math.h>


int main(int argc, char **argv){
    t_conf  conf;
    t_stats stats;
    t_opt   opt;

    if (!parse_input_get_conf(argv, &conf, &stats, &opt) || !init_socket(&conf))
        return 0;

    PRINT_HEADER_MSG(conf.dest_name_or_ip, stats.dest_ip, 1);

    while(1){

        intercept_and_handle_signals();
        send_ping(&conf, &stats);
        recv_pong(&conf, &stats);

        sleep(conf.interval_time);
    }
    print_stats_and_exit(&stats, conf.sockfd, conf.exit_status);
}
