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

# define MAX(x, y)      x > y ? x : y
# define MIN(x, y)      x < y ? x : y

# define ERROR_TTL_TOO_BIG(ttl) "ft_ping: option value too big: #ttl\n"
# define ERROR_INVALID_OPTION(opt) "ft_ping: invalid option -- '#opt'\nTry 'ping --help' or 'ping --usage' for more\n"
# define ERROR_INVALID_VALUE(value) "ft_ping: invalid value (`#value' near `#value')\n"
# define ERROR_OPTION_REQUIRE_ARG(arg) "ping: option 'arg' requires an argument\nTry 'ping --help' or 'ping --usage' for more information."



#endif