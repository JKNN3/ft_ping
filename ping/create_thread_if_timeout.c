#include "includes/ping.h"

static void *sleep_timeout_and_send_SIGINT(void *void_conf);

void    create_thread_if_timeout(t_opt *opt, t_conf *conf){

    if (!opt->timeout)
        return;

    pthread_t thread;

    pthread_create(&thread, NULL, sleep_timeout_and_send_SIGINT, (void *)conf);
    if (!opt->timeout)
        return;
}

static void *sleep_timeout_and_send_SIGINT(void *void_conf){
    t_conf *conf = (t_conf*)void_conf;

    sleep(conf->timeout);
    kill(conf->id, SIGINT);
    return NULL;
}