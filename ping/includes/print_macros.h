#ifndef PRINT_MACROS_H
# define PRINT_MACROS_H


/**     print header msg       **/

#define PRINT_HEADER_MSG(ip, bytes)\
printf("PING %s (%s): %d data bytes\n", ip, ip, bytes);

#define PRINT_HEADER_MSG_VERBOSE(ip, bytes, id)\
printf("PING %s (%s): %d data bytes, id %02x = %d\n", ip, ip, bytes, id, id);


/**     print packet stats      **/

#define PRINT_PACKET_STATS(ip, seq, ttl, time) \
printf("%d bytes from %s: icmp_seq=%hu ttl=%d time=%.1f ms\n", \
                            ICMP_MSG_LEN, ip, seq, ttl, time);


/**     print final statistics  **/

# define PRINT_FINAL_STATS(ip, nb_packets_sent, nb_packets_recv, loss_percentage,  \
                                total_time, rtt_min, rtt_avg, rtt_max, rtt_mdev)        \
printf("\n--- %s ping statistics ---\n\
%d packets transmitted, %d received, %d%% packet loss, time %.0Lfms\n\
rtt min/avg/max/mdev = %.3f/%.3Lf/%.3f/%.3f ms\n",\
ip, nb_packets_sent, nb_packets_recv, loss_percentage, total_time, rtt_min, rtt_avg, rtt_max, rtt_mdev);


/**     print SIGQUIT stats     **/

# define PRINT_SIGQUIT_STATS(nb_recv, nb_sent, loss, min, avg, ewma, max)            \
printf("%d/%d packets, %d%% loss, min/avg/ewma/max = %.3f/%.3f/%.3f/%.3f ms\n",        \
        nb_recv, nb_sent, loss, min, avg, ewma, max);




#endif