#include "ping.h"


int main(int argc, char **argv){
    if (argc < 2)
        return (0);

    struct addrinfo hints;
    struct addrinfo *res;

    struct ip ip_header;
    struct icmp icmp_;

    printf("sizeof ip_header: %lu\nsizeof icmp: %lu\n",sizeof(ip_header),sizeof(icmp_));

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


