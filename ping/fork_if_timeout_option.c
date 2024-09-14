#include "includes/ping.h"

void    fork_if_timeout(t_opt *opt, t_conf *conf){
    if (!opt->timeout)
        return;
    int pid = fork();
	if (pid == 0){
        sleep(conf->timeout);
        kill(conf->id, SIGINT);
        exit(0);
    }
}