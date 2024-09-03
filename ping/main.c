#include "includes/ping.h"


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

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    printf("sockfd fd: %d\n", sockfd);

    char *packet = malloc(sizeof(char) * 84);
    memset(packet, 0, sizeof((char) * packet));
    unsigned char data;
    printf("packet sizeof: %lu\n", sizeof(packet));
    fill_ip_header((struct ip*)packet, res, sockfd);

    char *tmp = packet + IP_HEADER_LEN ;
    fill_icmp_msg((struct icmp*)tmp);

    int send_status = sendto(sockfd, packet, 84, 0, res->ai_addr, sizeof(struct sockaddr));
    if (send_status < 0)
        perror("send status ");
    printf("send status: %d\n", send_status);
    printf("caca\n");
    freeaddrinfo(res);
    free(packet);
    close(sockfd);

    return (0);
}