#include "ping.h"


int main(int argc, char **argv){
    if (argc < 2)
        return (0);

    struct addrinfo hints;
    struct addrinfo *res = NULL;

    struct ip ip_header; // use ip and not iphdr for portability bcs iphdr is linux-specific
    struct icmp icmp_;

    printf("sizeof ip_header: %lu\nsizeof icmp: %lu\n",sizeof(ip_header),sizeof(icmp_));

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_CANONNAME;

    int ret = getaddrinfo(argv[1], NULL, &hints, &res);
    // char addrstr[100];
    // void *addr;
    // // struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
    // // addr = &((struct sockaddr_in *)p->ai_addr)sin_addr;
    //     // inet_ntop : This function converts the network address structure src in the af address family into a character string.
    // // test0 = &((struct sockaddr_in *) res->ai_addr)->sin_addr;

    // inet_ntop (res->ai_family, &((struct sockaddr_in *)res->ai_addr)->sin_addr, addrstr, 100);
    //   printf ("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
    //           addrstr, res->ai_canonname);
    
    // printf("res = %d\n", ret);
    // printf("res addrinfo:\nai_flags: %d\nai_family: %d\nai_socktype: %d\nai_protocol: %d\nai_addrlen: %d\nai_addr->sa_data: %s\nai_canonname: %s\n", res->ai_flags, res->ai_family, res->ai_socktype, res->ai_protocol, res->ai_addrlen, addrstr, res->ai_canonname);
    
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    printf("sockfd fd: %d\n", sockfd);

    // sendto(fd of the sending socket, message, msg len, flags, sockaddr du destinataire recup avec getaddrinfo, len de l'addr);
    // char test[50];
    // char *ptr = &test[0];
    // for (int i = 0; i < 50; i++){
    //     test[i] = 'a';
    // }
    // test[49] = '\0';
    // printf("test normal: %s\n", ptr);
    // ptr+=40;
    // printf("test +40 : %s\n", ptr);

    // sendto takes a const void buffer so i need to fill something being the size of my full packet
    //  i can use cast if i need it to be my struct ip or icmp msg.

    // i have to calculate checksum fot ip and icmp
        // checksum algorithm

    // recv()

    // check le paquet, recalculer checksum, calculer le timestamp

    // faire une routine pour makepacket sendto recvmsg, une boucle puis jsp voir comment on peut opti le truc plus tard

    // need a struct to store the informations that ping display at the end

    static char packet[IP_HEADER_LEN + ICMP_MSG_LEN];
    memset(packet, 0, sizeof(packet));
    unsigned char data;

    fill_ip_header((struct ip*)&packet, res->ai_addr, sockfd);


    fill_icmp_message((struct icmp*)(&packet[IP_HEADER_LEN]));

    // for (int i = 0; i < sizeof(packet); i++){ // print in hexa
    //     if (i % 8 == 0)
    //         printf ("  ");
    //     if (i % 16 == 0)
    //         printf ("\n");
    //     data = ((unsigned char*)&packet)[i];
    //     printf("%02x ", data);
    // }
    // printf ("\n");
    socklen_t dest_len = sizeof(res->ai_addr);

    int send_status = sendto(sockfd, (const void*)&packet, PACKET_LEN/2, 0, res->ai_addr, dest_len);
    if (send_status < 0)
        perror("send status ");
    printf("send status: %d\n", send_status);
    printf("caca\n");
    freeaddrinfo(res);
    close(sockfd);
    return (0);
}


// struct in_addr *get_src_ip_adress(int sockfd){
//     static struct ifreq ifr;  // for interface request (to fill the ip_header ip_src field)

//     memset(&ifr, 0, sizeof(ifr));
//     ifr.ifr_addr.sa_family = AF_INET;
//     strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);

//     if (ioctl(sockfd, SIOCGIFADDR, &ifr) >= 0)
//         return (&((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

//     perror("ioctl request failed getting src ip adress");
//     return (NULL);
// }

void    fill_ip_header(struct ip *ip_header, struct addrinfo *res, int sockfd){
/* 4 bits */     ip_header->ip_hl = IP_HEADER_LEN_IN_32BITS_INCREMENT;
/* 4 bits */     ip_header->ip_v = IP_VERSION;
/* 1 byte */    ip_header->ip_tos = 0;
/* 2 bytes*/    ip_header->ip_len = htons(IP_HEADER_LEN);
    ip_header->ip_id = htons(IP_ID);
    ip_header->ip_off = htons(SET_THE_DONT_FRAGMENT_THE_PACKET_BIT_TO_TRUE);
    ip_header->ip_ttl = TIME_TO_LIVE;
    ip_header->ip_p = IPPROTO_ICMP;
    ip_header->ip_sum = 0;
    //if (get_src_ip_adress(sockfd) == NULL)
    ip_header->ip_src.s_addr = INADDR_ANY;
    ip_header->ip_dst = ((struct sockaddr_in *)res)->sin_addr;

    ip_header->ip_sum = compute_checksum((void*)ip_header, IP_HEADER_LEN); // -> u_short () 2 bytes
}


void    fill_icmp_message(struct icmp *icmp_message){
/* 1 byte */    icmp_message->icmp_type = ICMP_ECHO;
/* 1 byte */    icmp_message->icmp_code = ICMP_ECHOREPLY;
/* 2 bytes*/    icmp_message->icmp_cksum = 0;
/* 2 bytes*/    icmp_message->icmp_id = 2; // mike muss did : in = getpid() & 0xFFFF pour avoir juste les 16 derniers bits
                                // car c'est un u_int_16. C'est important poiur l'identification du paquet retour;
/* 2 bytes*/    icmp_message->icmp_seq= 3; // nombre de paquets transmis, a ++ quand on envoie un paquet, struct principale.

                void *icmp_timeval = (void*)icmp_message + ICMP_HEADER_LEN;
/* 16 bytes */  int ret_gettime = gettimeofday((struct timeval *)icmp_timeval, NULL); //check ça  
                printf("gettime return: %d\n", ret_gettime);
                icmp_message->icmp_cksum = compute_checksum((void *)icmp_message, ICMP_HEADER_LEN); // -> u_int16_t 2 bytes mais quand on a fini de remplir la struct huh


/* payload 40 bytes */
}



void    send_echo_request_packet(int sockfd){
    static char packet[IP_HEADER_LEN + ICMP_MSG_LEN];
    // fill_ip_header();
    // fill_icmp_message();
    // sendto(sockfd, (void*)packet, PACKET_LEN, 0, (const struct sockaddr*)res->ai_addr, sizeof(res->ai_addr));
    // sendto(fd of the sending socket, message, msg len, flags, sockaddr du destinataire recup avec getaddrinfo, len de l'addr);

}

void    recv_echo_reply_packet(){
    return;
}

void    check_received_packet(){
    return;
}

void    print_statistics(){
    return;
    //     unix-history-repo/usr/src/etc/ping.c line 416:
    // Heavily buffered STDIO is used here, so that all the statistics
    // will be written with 1 sys-write call.  This is nice when more
    // than one copy of the program is running on a terminal;  it prevents
    // the statistics output from becomming intermingled.
}