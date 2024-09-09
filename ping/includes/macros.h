#ifndef MACROS_H
# define MACROS_H

# define IP_HEADER_LEN_IN_32BITS_INCREMENT              5           // in 32 bits increments
# define IP_VERSION                                     4
# define IP_HEADER_LEN                                  20          // bytes
# define TIME_TO_LIVE                                   64
# define ICMP_HEADER_LEN                                8           // bytes
# define ICMP_MSG_LEN                                   64          // bytes
# define PACKET_LEN                                     84          // bytes
# define ICMP_PAYLOAD_DATA_LEN                          40
# define IP_ID                                          21
# define SET_THE_DONT_FRAGMENT_THE_PACKET_BIT_TO_TRUE   (1 << 14)   //set the 'dont fragment the packet' bit (bit 01) to true
# define ICMP_TIMESTAMP_LEN                             16          // bytes
# define ICMP_PAYLOAD_STARTING_BYTE                     44

# define MAX(x, y)      x > y ? x : y
# define MIN(x, y)      x < y ? x : y


        // faire un truc if -v define verbose et autre define avec bonne string

/**     print initial msg           **/
#define PRINT_HEADER_MSG(ip, bytes)\
printf("PING %s (%s) %d(%d) bytes of data.\n", ip, ip, bytes, PACKET_LEN);

/**     print packet stats          **/
#define PRINT_PACKET_STATS(ip, seq, ttl, time) \
printf("%d bytes from %s: icmp_seq=%hu ttl=%d time=%.1f ms\n", \
                            ICMP_MSG_LEN, ip, seq, ttl, time);

/**     print final statistics      **/
# define PRINT_FINAL_STATS(ip, nb_packets_sent, nb_packets_recv, loss_percentage,  \
                                total_time, rtt_min, rtt_avg, rtt_max, rtt_mdev)        \
printf("--- %s ping statistics ---\n\
%d packets transmitted, %d received, %d%% packet loss, time %.0Lfms\n\
rtt min/avg/max/mdev = %.3f/%.3Lf/%.3f/%.3f ms\n",\
ip, nb_packets_sent, nb_packets_recv, loss_percentage, total_time, rtt_min, rtt_avg, rtt_max, rtt_mdev);


// penser a faire les opérrations simples avec des ternaires, on peut les define


#endif