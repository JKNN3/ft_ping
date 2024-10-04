#ifndef PRINT_MACROS_H
# define PRINT_MACROS_H


/**     print header msg       **/

#define PRINT_HEADER_MSG(ip_arg, ip, bytes)\
printf("PING %s (%s%s%s): %d data bytes\n", ip_arg, PURPLE, ip, WHITE, bytes);

#define PRINT_HEADER_MSG_VERBOSE(ip_arg, ip, bytes, id)\
printf("PING %s (%s%s%s): %d data bytes, id 0x%02x = %d\n", ip_arg, PURPLE, ip, WHITE, bytes, id, id);

/**     print packet stats      **/

#define PRINT_PACKET_STATS(bytes_recv, ip, seq, ttl, time) \
printf("%d bytes from %s%s%s: icmp_seq=%hu ttl=%d time=%s%.3f%s ms\n", \
                            bytes_recv, PURPLE, ip, WHITE, seq, ttl, PINK, time, WHITE);
#define PRINT_PACKET_ERR(bytes_recv, ip, err)\
printf("%d bytes from %s%s%s: %s\n", bytes_recv, PURPLE, ip, WHITE, err);

/**     print final statistics  **/

# define PRINT_FINAL_STATS(ip, nb_packets_sent, nb_packets_recv, loss_percentage,  \
                                rtt_min, rtt_avg, rtt_max, rtt_stddev)        \
printf("--- %s ping statistics ---\n\
%d packets transmitted, %d packets received, %d%% packet loss\n\
round-trip "BLUE"min"WHITE"/"PURPLE"avg"WHITE"/"PINK"max"WHITE"/"YELLOW"stddev"WHITE" = \
"BLUE"%.3f"WHITE"/"PURPLE"%.3Lf"WHITE"/"PINK"%.3f"WHITE"/"YELLOW"%.3f"WHITE" ms\n",\
ip, nb_packets_sent, nb_packets_recv, loss_percentage, rtt_min, rtt_avg, rtt_max, rtt_stddev);

#define PRINT_FINAL_STATS_NO_RECV(ip, nb_packets_sent, nb_packets_recv, loss_percentage)\
printf("--- %s ping statistics ---\n\
%d packets transmitted, %d packets received, %d%% packet loss\n",\
ip, nb_packets_sent, nb_packets_recv, loss_percentage);

/**     print SIGQUIT stats     **/

# define PRINT_SIGQUIT_STATS(nb_recv, nb_sent, loss, min, avg, stddev, max)            \
printf("%d/%d packets, %d%% loss, "BLUE"min"WHITE"/"PURPLE"avg"WHITE"/"PINK"stddev"WHITE"/"YELLOW"max"WHITE" = \
"BLUE"%.3f"WHITE"/"PURPLE"%.3f"WHITE"/"PINK"%.3f"WHITE"/"YELLOW"%.3f"WHITE" ms\n",        \
        nb_recv, nb_sent, loss, min, avg, stddev, max);

# define PRINT_USAGE \
printf("Usage: ping [-dcfv?] [-c NUMBER] [-i NUMBER] [-T NUM] [-w N]\n\
            [--debug] [--ttl=N] [--verbose] [--timeout=N] [--flood]\n\
            [--quiet] [--help] [--usage] [--version]\n\
            HOST ...\n");


#define PRINT_HELP \
printf("Usage: ping [OPTION...] HOST ...\n\
Send ICMP ECHO_REQUEST packets to network hosts.\n\
                                                                                \
 Options available for ping echo requests:\n\
\n\
  -c, --count=NUMBER         stop after sending NUMBER packets\n\
  -d, --debug                set the SO_DEBUG option\n\
  -i, --interval=NUMBER      wait NUMBER seconds between sending each packet\n\
  -n, --numeric              do not resolve host addresses\n\
      --ttl=N                specify N as time-to-live\n\
  -v, --verbose              verbose output\n\
  -w, --timeout=N            stop after N seconds\n\
  -f, --flood                flood ping (root only)\n\
\n\
  -p, --pattern=PATTERN      fill ICMP packet with given pattern (hex)\n\
  -q, --quiet                quiet output\n\
\n\
  -?, --help                 give this help list\n\
      --usage                give a short usage message\n\
  -V, --version              print program version\n\
\n\
Mandatory or optional arguments to long options are also mandatory or optional\n\
for any corresponding short options.\n\
\n\
Options marked with (root only) are available only to superuser.\n");


#endif