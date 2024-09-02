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

void    fill_ip_header(struct ip *ip_header, char dest_str[100]);
void    fill_icmp_message(struct icmp *icmp_message);
short   compute_checksum(void *packet, int len); // len = longueur du packet en octets/bytes
void    print_memory(char *memory);

#endif