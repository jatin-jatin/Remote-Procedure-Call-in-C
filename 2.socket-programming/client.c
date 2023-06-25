#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include "config.h"

int main(){
    int send_data=101;
    int recv_data=-1;
    struct sockaddr_in dest;
    int sockfd=0,len=0,recv_size=0;
    int addr_len;

    // setting destination address
    dest.sin_family=AF_INET;
    dest.sin_port=htons(SERVER_PORT);
    struct hostent *host = (struct hostent *)gethostbyname(SERVER_IP);
    dest.sin_addr = *((struct in_addr*)host->h_addr_list[0]);
    addr_len = sizeof(struct sockaddr);

    // socket for sending data
    if((sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
        perror("Socket creation failed\n");
        exit(1);
    }

    // data sent
    printf("send data: %d\n",send_data);
    len= sendto(sockfd,(char*)&send_data,sizeof(int),0,(struct sockaddr*)&dest,sizeof(struct sockaddr));
    printf("No of bytes sent:%d\n",len);
    // data + 1 received
    len= recvfrom(sockfd,(char*)&recv_data,MAX_RECV_SEND_BUFF_SIZE,0,(struct sockaddr*)&dest,&addr_len);
    printf("-----------------------------------\n");
    printf("recv data: %d\n",recv_data);
    printf("No of bytes received: %d\n",len);

    return 0;
}