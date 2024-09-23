#include "../includes/ping.h"

int main(int argc, char **argv){

    (void) argc;
    t_conf  conf;
    t_stats stats;
    t_opt   opt;

    if (!parse_input_get_conf(argv, &conf, &stats, &opt) || !init_socket(&opt, &conf))
        return 0;

    print_header(&opt, &conf, &stats);
    create_thread_if_timeout(&opt, &conf);
    while(TRUE){

        if (opt.count && !check_count_option(&conf))
                break;

        intercept_and_handle_signals();
        send_ping(&conf, &stats, &opt);
        recv_pong(&conf, &stats, &opt);

        sleep(conf.interval_time);
    }
    print_final_stats_and_exit(&stats, 0);
    return 0;
}
