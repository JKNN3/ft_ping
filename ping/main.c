#include "includes/ping.h"

/*
          TO DO

    - find why everything is double when localhost
    - compute stddev
    - le hexdump de verbose
    - pouvoir mettre plusieurs argum,ents a la suite genre -fq etc

        options:
    - audible
    - debug
    - count         trouver comment faire sans checker a chaque tour de boucle
    - flood         OK reste a savoir si il faut laisser le root check ou pas
    - help          OK
    - interval      OK
    - quiet         OK
    - timeout       OK
    - time to live  OK
    - usage         OK
    - verbose       

    y'a des trucs a revoir dans le parsing eeeeee:

k: ping --print  1.1.1.1
    ping: unrecognized option '--print'
    Try 'ping --help' or 'ping --usage' for more information.

k: ping -print  1.1.1.1
    ping: error in pattern near rint


          TO DO NEXT

  ~ maybe find a way to make valgrind work URGH

*/
# include <math.h>


int main(int argc, char **argv){

    t_conf  conf;
    t_stats stats;
    t_opt   opt;

    if (!parse_input_get_conf(argv, &conf, &stats, &opt) || !init_socket(&conf))
        return 0;

    print_header(&opt, &conf, &stats);
    fork_if_timeout(&opt, &conf);

    while(1){

        intercept_and_handle_signals();
        send_ping(&conf, &stats);
        recv_pong(&conf, &stats, &opt);

        sleep(conf.interval_time);
    }
    print_stats_and_exit(&stats, conf.exit_status);
}
