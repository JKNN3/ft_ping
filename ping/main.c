#include "includes/ping.h"



int main(int argc, char **argv){
    t_conf conf;

    if (!parse_input_get_conf(argv[1], &conf) || !init_socket(&conf))
        return 0;

    send_ping(&conf);

    close(conf.sockfd);
    return (0);
}