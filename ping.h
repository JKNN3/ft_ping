#ifndef PING_H
# define PING_H

#include <stdio.h>              // printf
#include <string.h>             // memset()
#include <regex.h>
#include <unistd.h>             // write()
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>              // socket(), getaddrinfo()
#include <netinet/in.h>
#include <netinet/ip.h>         // struct ip
#include <netinet/ip_icmp.h>    // struct icmp
#include <arpa/inet.h>          // inet_ntop()


#include "macros.h"
#include "regex.h"



#endif