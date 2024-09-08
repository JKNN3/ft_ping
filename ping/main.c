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
    t_conf conf;

    if (!parse_input_get_conf(argv[1], &conf) || !init_socket(&conf))
        return 0;

    send_ping(&conf);

    close(conf.sockfd);
    return (0);
}