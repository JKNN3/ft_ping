#include "ping.h"


int main(int argc, char **argv){
    if (argc < 2)
        return (0);

    struct addrinfo hints;
    struct addrinfo *res;

    struct ip ip_header; // use ip and not iphdr for portability bcs iphdr is linux-specific
    struct icmp icmp_;

    printf("sizeof ip_header: %lu\nsizeof icmp: %lu\n",sizeof(ip_header),sizeof(icmp_));

    //

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;

    int ret = getaddrinfo(argv[1], NULL, &hints, &res);

    printf("res addrinfo:\nai_flags: %d\nai_family: %d\nai_socktype: %d\nai_protocol: %d\nai_addrlen: %d\nai_canonname: %s\n", res->ai_flags, res->ai_family, res->ai_socktype, res->ai_protocol, res->ai_addrlen, res->ai_canonname);
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

    // faire uneroutine pour makepacket send recv, une boucle puis jsp voir comment on peut opti le truc plus tard

    // need a struct to store the informations that ping display at the end

    freeaddrinfo(res);
    return (0);
}

void    fill_ip_header(struct ip *ip_header){
    // ip_header.ip_tos = type_of_service
    // ip_header.ip_len =
    // ip_header.ip_id = 
    // ip_header.ip_off =
    // ip_header.ip_ttl = 
    // ip_header.ip_p = protocol
    // ip_header.ip_sum = compute_checksum(); // -> u_short () 2 bytes
    // ip_header.ip_src = 
    // ip_header.ip_dest = // struct in_addr 
                        // in_addr_t is equivalent to the type uint32_t as defined in <inttypes.h> .
                        // use https://stackoverflow.com/questions/76940582/why-struct-in-addr-is-needed
}

void    fill_icmp_message(struct icmp *icmp_message){
    icmp_message.icmp_type = ICMP_ECHO;
    icmp_message.icmp_code = 0;
    // icmp_message.icmp_cksum = compute_checksum(); // -> u_int16_t 2 bytes
}

u_short compute_checksum(){
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

}