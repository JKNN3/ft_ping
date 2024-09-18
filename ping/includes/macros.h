#ifndef MACROS_H
# define MACROS_H


# define IP_HEADER_LEN_IN_32BITS_INCREMENT              5           // in 32 bits increments
# define IP_VERSION                                     4
# define IP_HEADER_LEN                                  20          // bytes
# define ICMP_HEADER_LEN                                8           // bytes
# define ICMP_MSG_LEN                                   64          // bytes
# define PACKET_LEN                                     84          // bytes
# define ICMP_PAYLOAD_DATA_LEN                          40          // bytes
# define SET_THE_DONT_FRAGMENT_THE_PACKET_BIT_TO_TRUE   (1 << 14)   //set the 'dont fragment the packet' bit (bit 01) to true
# define ICMP_TIMESTAMP_LEN                             16          // bytes
# define ICMP_PAYLOAD_STARTING_BYTE                     44
# define DATA_BYTES                                     56
# define MAX(x, y)      x > y ? x : y
# define MIN(x, y)      x < y ? x : y

# define MAKE_SOUND printf("\a")

# define PACKET_DUMP_IP_HEADER "IP Hdr Dump:\n"
# define PACKET_DUMP_IP_DETAILS "Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src	Dst	Data\n"

#endif