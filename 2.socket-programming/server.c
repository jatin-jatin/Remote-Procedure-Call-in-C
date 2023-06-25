#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include "config.h"

int main(){
    int recv_data=-1;
    int send_data=-1;
    int sock_upd_fd =0,len,addr_len,opt=1,
        reply_msg_size=0;
    struct sockaddr_in server_addr,client_addr;
    if((sock_upd_fd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
        perror("Socket creation failed\n");
        exit(1);
    }
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(SERVER_PORT);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    addr_len = sizeof(struct sockaddr);

    if(setsockopt(sock_upd_fd,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt))<0){
        perror("setsockopt failed\n");
        exit(1);
    }
    if(setsockopt(sock_upd_fd,SOL_SOCKET, SO_REUSEPORT ,(char*)&opt,sizeof(opt))<0){
        perror("setsockopt failed\n");
        exit(1);
    }

    if(bind(sock_upd_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))==-1){
        perror("socket bind failed\n");
    }
    len = recvfrom(sock_upd_fd,(char*)&recv_data,MAX_RECV_SEND_BUFF_SIZE,0,(struct sockaddr*)&client_addr,&addr_len);
    printf("No of bytes received:%d\n",len);
    printf("Data received %d\n",recv_data);
    send_data=recv_data+1;

    len = sendto(sock_upd_fd,&send_data,sizeof(int),0,(struct sockaddr*)&client_addr,sizeof(struct sockaddr));
    printf("-----------------------------------\n");
    printf("send_data:%d\n",send_data);
    printf("No of bytes sent:%d\n",len);

    return 0;
}