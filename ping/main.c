#include "includes/ping.h"

bool    get_dest_addr(char *addr, t_data *ping_conf){

    struct addrinfo hints;
    struct addrinfo *res = NULL;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_CANONNAME;

    ping_conf->dest.sin_family = AF_INET;
    if (getaddrinfo(addr, NULL, &hints, &res)){
        freeaddrinfo(res);
        perror("getaddrinfo failed ");
        return 0;
    }

    ping_conf->dest = *((struct sockaddr_in*)res->ai_addr);
    freeaddrinfo(res);
    return 1;
}

int main(int argc, char **argv){
    if (argc < 2)
        return (0);

    t_data ping_conf;
    if (!get_dest_addr(argv[1], &ping_conf))
        return 0;


    ping_conf.sockfd = socket(PF_INET, SOCK_RAW, 0);
    int opt_value = 1;
    if (setsockopt(ping_conf.sockfd, IPPROTO_IP, IP_HDRINCL, &opt_value, sizeof(int)) != 0){
        perror("setsockopt failed ");
    }       // 



    //char packet[PACKET_LEN];
    char *packet = malloc(sizeof(char) * PACKET_LEN);
    memset(packet, 2, PACKET_LEN);
    // for(int i = 0; i < PACKET_LEN; i++){
    //     packet[i] = i + '0';
    // }
    // packet[PACKET_LEN - 1] = '\0';

    unsigned char data;
    for (int i = 0; i < PACKET_LEN; i++){ // print in hexa
        if (i % 8 == 0)
            printf ("  ");
        if (i % 16 == 0)
            printf ("\n");
        data = ((unsigned char*)packet)[i];
        printf("%02x ", data);
    }
    printf ("\n");

    fill_ip_header((struct ip*)packet, &ping_conf);


    fill_icmp_msg((struct icmp*)(packet + IP_HEADER_LEN));

    for(int i = (IP_HEADER_LEN + ICMP_HEADER_LEN + 16); i < PACKET_LEN; i++){
        packet[i] = i + '0';
    }
    packet[PACKET_LEN - 1] = '\0';

    for (int i = 0; i < PACKET_LEN; i++){ // print in hexa
       if (i % 8 == 0)
           printf ("  ");
       if (i % 16 == 0)
           printf ("\n");
       data = ((unsigned char*)packet)[i];
       printf("%02x ", data);
    }
    printf ("\n");


    int send_status = sendto(ping_conf.sockfd, packet, PACKET_LEN, 0, (const struct sockaddr*)&ping_conf.dest, sizeof(struct sockaddr));
    if (send_status < 0)
        perror("send status ");
    printf("send status: %d\n", send_status);
    free(packet);
    close(ping_conf.sockfd);

    return (0);
}