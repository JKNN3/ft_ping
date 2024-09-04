#include "includes/ping.h"

/*
          TO DO

    - find why checksum isn't working properly 
    - complete offset field and co
    - make my ping work


          TO DO NEXT

    - parsing
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