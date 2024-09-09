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

int main(int argc, char **argv){
    t_conf  conf;
    t_stats stats;
    if (!parse_input_get_conf(argv[1], &conf, &stats) || !init_socket(&conf))
        return 0;

    PRINT_HEADER_MSG(conf.dest_ip, 1);

    send_ping(&conf);
    recv_pong(&conf, &stats);


    PRINT_FINAL_STATS(conf.dest_ip,                                                                 \
                      conf.nb_packets_transmitted-1,                                                \
                      stats.nb_packets_received,                                                    \
                      100 - ((stats.nb_packets_received / (conf.nb_packets_transmitted-1)) * 100),  \
                      stats.total_time_ms,                                                          \
                      stats.rtt_min,                                                               \
                      (stats.total_time_ms / stats.nb_packets_received),                            \
                      stats.rtt_max,                                                               \
                      0.0);
    close(conf.sockfd);
    return (0);
}