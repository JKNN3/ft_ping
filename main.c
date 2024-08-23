#include "ping.h"


int main(int argc, char **argv){
    if (argc < 2)
        return (0);

    struct addrinfo hints;
    struct addrinfo *res;

    struct ip ip_header; // use ip and not iphdr for portability bcs iphdr is linux-specific
    struct icmp icmp_;

    printf("sizeof ip_header: %lu\nsizeof icmp: %lu\n",sizeof(ip_header),sizeof(icmp_));

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_CANONNAME;

    int ret = getaddrinfo(argv[1], NULL, &hints, &res);
    char addrstr[100];
    void *addr;
    // struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
    // addr = &((struct sockaddr_in *)p->ai_addr)sin_addr;
        // inet_ntop : This function converts the network address structure src in the af address family into a character string.
    // test0 = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
    
    // ca maaaarche ahaha
    inet_ntop (res->ai_family, &((struct sockaddr_in *)res->ai_addr)->sin_addr, addrstr, 100);
      printf ("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
              addrstr, res->ai_canonname);
    
    printf("res = %d\n", ret);
    printf("res addrinfo:\nai_flags: %d\nai_family: %d\nai_socktype: %d\nai_protocol: %d\nai_addrlen: %d\nai_addr->sa_data: %s\nai_canonname: %s\n", res->ai_flags, res->ai_family, res->ai_socktype, res->ai_protocol, res->ai_addrlen, addrstr, res->ai_canonname);
    int sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);

    // sendto(fd of the sending socket, message, msg len, flags, sockaddr du destinataire recup avec getaddrinfo, len de l'addr);
    char test[50];
    char *ptr = &test[0];
    for (int i = 0; i < 51; i++){
        test[i] = 'a';
    }
    printf("test normal: %s\n", ptr);
    ptr+=40;
    printf("test +40 : %s\n", ptr);

    // sendto takes a const void buffer so i need to fill something being the size of my full packet
    //  i can use cast if i need it to be my struct ip or icmp msg.

    // i have to calculate checksum fot ip and icmp
        // checksum algorithm

    // recv()

    // check le paquet, recalculer checksum, calculer le timestamp

    // faire une routine pour makepacket sendto recvmsg, une boucle puis jsp voir comment on peut opti le truc plus tard

    // need a struct to store the informations that ping display at the end

    freeaddrinfo(res);
    return (0);
}

void    fill_ip_header(struct ip *ip_header, char dest_str[100]){
    ip_header->ip_hl = IP_HEADER_LEN;
    ip_header->ip_v = IP_VERSION;
    ip_header->ip_tos = 0;
    ip_header->ip_len = IP_TOTAL_LEN;

    ip_header->ip_id = 0; // ??

    ip_header->ip_off = SET_DONT_FRAGMENT_BIT_TRUE ;
    ip_header->ip_ttl = TIME_TO_LIVE
    ip_header->ip_p = IPPROTO_ICMP ;
    // ip_header->ip_sum = compute_checksum(); // -> u_short () 2 bytes
    ip_header->ip_src = INADDR_ANY;
    if (!inet_aton(dest_str, ip_header->ip_dest.s_addr)) // met ip adresse bon format
        return; // puterror eeeh
}

void    fill_icmp_message(struct icmp *icmp_message){
    icmp_message->icmp_type = ICMP_ECHO;
    icmp_message->icmp_code = ICMP_ECHOREPLY;
    // icmp_message->icd_id = ; // mike muss did : in = getpid() & 0xFFFF pour avoir juste les 16 derniers bits
                                // car c'est un u_int_16. C'est important poiur l'identification du paquet retour;
    // icmp_message->icd_seq= ; // nombre de paquets transmis, a ++ quand on envoie un paquet, struct principale.
    
    // timestamp ? clock_gettime()

    // icmp_message.icmp_cksum = compute_checksum(); // -> u_int16_t 2 bytes mais quand on a fini de remplir la struct huh

}

u_short compute_checksum(){


    return (0);
}                                                                            

void    send_echo_request_packet(){
    // fill_ip_header();
    // fill_icmp_message();
}

void    recv_echo_reply_packet(){

}

void    check_received_packet(){

}

void    print_statistics(){
    //     unix-history-repo/usr/src/etc/ping.c line 416:
    // Heavily buffered STDIO is used here, so that all the statistics
    // will be written with 1 sys-write call.  This is nice when more
    // than one copy of the program is running on a terminal;  it prevents
    // the statistics output from becomming intermingled.
}