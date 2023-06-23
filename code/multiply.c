#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include"rpc_common.h"
#include"serialize.h"

ser_buff_t *
multiply_client_stub_marshal(int a,int b){
    ser_buff_t *buffer=NULL;
    init_serialized_buffer_of_defined_size(&buffer,MAX_RECV_SEND_BUFF_SIZE);

    serialize_data(buffer,(char*)&a,sizeof(int));
    serialize_data(buffer,(char*)&b,sizeof(int));

    return buffer;
}

void rpc_send_recv(ser_buff_t *client_send, ser_buff_t *client_recv){
    struct sockaddr_in dest;
    int sockfd = 0, rc=0,recv_size=0;
    int addr_len;

    dest.sin_family=AF_INET;
    dest.sin_port = htons(SERVER_PORT);

    struct hostent *host = (struct hostent*)gethostbyname(SERVER_IP);
    dest.sin_addr=*((struct in_addr*)host->h_addr_list[0]);

    addr_len = sizeof(struct sockaddr);
    sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd==-1){
        printf("socket creation failed\n");
        return -1;
    }
    rc = sendto(sockfd,client_send->b,get_serialize_buffer_length(client_send),
    0,(struct sockaddr*)&dest,sizeof(struct sockaddr));

    printf("%s() : %d bytes sent\n",__FUNCTION__,rc);
}

int multiply_rpc(int a, int b){

    ser_buff_t *client_send_ser_buffer = multiply_client_stub_marshal(a,b);
    ser_buff_t *client_recv_ser_buffer = NULL;

    init_serialized_buffer_of_defined_size(&client_send_ser_buffer,MAX_RECV_SEND_BUFF_SIZE);

    rpc_send_recv(client_send_ser_buffer,client_recv_ser_buffer);

    free(client_send_ser_buffer);
    client_send_ser_buffer=NULL;
}

int main(int argc,char **argv){

    int a,b;
    printf("Enter 1st number : ");
    scanf("%d",&a);
    printf("Enter 2st number : ");
    scanf("%d",&b);

    int res = multiply_rpc(a,b);

    printf("res = %d\n",res);
    return 0;
}