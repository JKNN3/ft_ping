#ifndef PING_H
# define PING_H

# include <stdio.h>                 // printf
# include <string.h>                // memset()
# include <regex.h> 
# include <unistd.h>                // write()
# include <sys/types.h> 
# include <sys/socket.h>    
# include <netdb.h>                 // socket(), getaddrinfo()
# include <netinet/in.h>    
# include <netinet/ip.h>            // struct ip
# include <netinet/ip_icmp.h>       // struct icmp
# include <arpa/inet.h>             // inet_ntop()
# include <sys/time.h>              // gettimeofday()
# include <errno.h>
# include "macros.h"
# include "regex.h"
# include <sys/ioctl.h>             // ioctl() and ifreq struct
# include <net/if.h>                // IFNAMSIZ constant
# include <stdlib.h>                // malloc
# include <stdbool.h>               // TRUE, FALSE 

typedef struct s_data{
    int                     sockfd;
    struct sockaddr_in      dest;
    short                   nb_packets_sent;
    
} t_data ; 

/*          fill_packet.h           */
void    fill_ip_header(struct ip *ip_header,t_data *ping_conf);
void    fill_icmp_msg(struct icmp *icmp_message);

/*          compute_checksum.h      */
short   compute_checksum(void *packet, int len); // len = longueur du packet en octets/bytes



#endif