#include "../../includes/ping.h"

static void *sleep_timeout_and_send_SIGINT(void *void_conf);

void    create_thread_if_timeout(t_opt *opt, t_conf *conf){

    if (!opt->timeout)
        return;

    pthread_create(get_thread(), NULL, sleep_timeout_and_send_SIGINT, (void *)conf);
    pthread_detach(*get_thread());
    get_timeout_status(SET);
}

static void *sleep_timeout_and_send_SIGINT(void *void_conf){
    t_conf *conf = (t_conf*)void_conf;
    int sleep_duration_ms = conf->timeout * 1000;

    for (int i = 0; i <= sleep_duration_ms; i += 50) {
        usleep(50000);
    }
    kill(conf->id, SIGINT);
    pthread_exit(NULL);
}

bool    get_timeout_status(bool request){
    static bool status;
    if (request == GET)
        return status;
    status = true;
    return FALSE;
}

pthread_t *get_thread(){
    static pthread_t thread;
    return &thread;
}