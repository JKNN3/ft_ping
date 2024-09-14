#ifndef PRINT_MACROS_H
# define PRINT_MACROS_H


/**     print header msg       **/

#define PRINT_HEADER_MSG(ip_arg, ip, bytes)\
printf("PING %s (%s): %d data bytes\n", ip_arg, ip, bytes);

#define PRINT_HEADER_MSG_VERBOSE(ip_arg, ip, bytes, id)\
printf("PING %s (%s): %d data bytes, id %02x = %d\n", ip_arg, ip, bytes, id, id);


/**     print packet stats      **/

#define PRINT_PACKET_STATS(bytes_recv, ip, seq, ttl, time) \
printf("%d bytes from %s: icmp_seq=%hu ttl=%d time=%.3f ms\n", \
                            bytes_recv, ip, seq, ttl, time);

#define PRINT_PACKET_ERR(bytes_recv, ip, err)\
printf("%d bytes from %s: %s\n", bytes_recv, ip, err);

/**     print final statistics  **/

# define PRINT_FINAL_STATS(ip, nb_packets_sent, nb_packets_recv, loss_percentage,  \
                                rtt_min, rtt_avg, rtt_max, rtt_mdev)        \
printf("--- %s ping statistics ---\n\
%d packets transmitted, %d packets received, %d%% packet loss\n\
round-trip min/avg/max/stddev = %.3f/%.3Lf/%.3f/%.3f ms\n",\
ip, nb_packets_sent, nb_packets_recv, loss_percentage, rtt_min, rtt_avg, rtt_max, rtt_mdev);

#define PRINT_FINAL_STATS_NO_RECV(ip, nb_packets_sent, nb_packets_recv, loss_percentage)\
printf("--- %s ping statistics ---\n\
%d packets transmitted, %d packets received, %d%% packet loss\n",\
ip, nb_packets_sent, nb_packets_recv, loss_percentage);

/**     print SIGQUIT stats     **/

# define PRINT_SIGQUIT_STATS(nb_recv, nb_sent, loss, min, avg, ewma, max)            \
printf("%d/%d packets, %d%% loss, min/avg/ewma/max = %.3f/%.3f/%.3f/%.3f ms\n",        \
        nb_recv, nb_sent, loss, min, avg, ewma, max);




#endif