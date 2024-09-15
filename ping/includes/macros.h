#ifndef MACROS_H
# define MACROS_H

# define IP_HEADER_LEN_IN_32BITS_INCREMENT              5           // in 32 bits increments
# define IP_VERSION                                     4
# define IP_HEADER_LEN                                  20          // bytes
# define ICMP_HEADER_LEN                                8           // bytes
# define ICMP_MSG_LEN                                   64          // bytes
# define PACKET_LEN                                     84          // bytes
# define ICMP_PAYLOAD_DATA_LEN                          40
# define IP_ID                                          21
# define SET_THE_DONT_FRAGMENT_THE_PACKET_BIT_TO_TRUE   (1 << 14)   //set the 'dont fragment the packet' bit (bit 01) to true
# define ICMP_TIMESTAMP_LEN                             16          // bytes
# define ICMP_PAYLOAD_STARTING_BYTE                     44
# define DATA_BYTES                                     56
# define MAX(x, y)      x > y ? x : y
# define MIN(x, y)      x < y ? x : y

# define ERROR_TTL_TOO_BIG(ttl) fprintf(stderr, "ft_ping: option value too big: %s\n", ttl)
# define ERROR_INVALID_VALUE(value) fprintf(stderr, "ft_ping: invalid value (`%s' near `%s')\n", value, value)
# define ERROR_OPTION_REQUIRE_ARG(option) fprintf(stderr, "ping: option '%s' requires an argument\nTry 'ping --help' or 'ping --usage' for more information.\n", option)
# define ERROR_CORE_DUMP fprintf(stderr, "Quit (core dumped)\n")
# define ERROR_TIMEOUT_VALUE_TOO_SMALL(value) fprintf(stderr, "ft_ping: option value too small: %ld\n", value)
# define ERROR_TIMEOUT_VALUE_TOO_BIG(value) fprintf(stderr, "ft_ping: option value too big: %ld\n", value)
# define ERROR_INVALID_OPTION(opt) fprintf(stderr, "ft_ping: invalid option -- '%s'\nTry 'ping --help' or 'ping --usage' for more information.\n", opt)
# define ERROR_UNKNOWN_HOST fprintf(stderr, "ft_ping : unknown host\n")
# define ERROR_COMPILING_REGEX fprintf(stderr, "An error occured compiling regex.\n")
# define ERROR_NEED_TO_BE_ROOT fprintf(stderr, "You need to be root\n")

#endif