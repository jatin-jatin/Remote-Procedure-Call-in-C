#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include"rpc_common.h"
#include"serialize.h"

int multiply(int a,int b){
    return a*b;
}

int multiply_server_stub_unmarshal(ser_buff_t *server_recv_ser_buffer){

    int a,b;
    de_serialize_data((char*)&a,server_recv_ser_buffer,sizeof(int));
    de_serialize_data((char*)&b,server_recv_ser_buffer,sizeof(int));
    return multiply(a,b);
}
void rpc_server_process_msg(ser_buff_t *server_recv_ser_buffer,ser_buff_t *server_send_ser_buffer){
    int res = multiply_server_stub_unmarshal(server_recv_ser_buffer);

    // serialize_data(server_send_ser_buffer,(char*)&res,sizeof(int));
}

int main(int argc, char **argv){
    int sock_udp_fd=0,len,
    addr_len,opt=1,reply_msg_size=0;

    struct sockaddr_in server_addr,client_addr;

    if((sock_udp_fd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
        printf("socket creation failed\n");
        exit(1);
    }

    server_addr.sin_family=AF_INET; 
    server_addr.sin_port=htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    addr_len = sizeof(struct sockaddr);

    if(setsockopt(sock_udp_fd,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt)<0)){
        perror("setsockopt");
        // exit(EXIT_FAILURE);
        exit(1);
    }// *2 times but I am keeping it one time.

    if(bind(sock_udp_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))==-1){
        printf("socket bind failed\n");
        exit(1);
    }

    ser_buff_t *server_recv_ser_buffer=NULL,
               *server_send_ser_buffer=NULL;

    init_serialized_buffer_of_defined_size(&server_recv_ser_buffer,
        MAX_RECV_SEND_BUFF_SIZE);
    init_serialized_buffer_of_defined_size(&server_send_ser_buffer,
        MAX_RECV_SEND_BUFF_SIZE);
    
    printf("Server ready to service rpc calls");

while(1){
    reset_serialize_buffer(server_recv_ser_buffer);

    len = recvfrom(sock_udp_fd,server_recv_ser_buffer->b,
                    get_serialize_buffer_length(server_recv_ser_buffer),
                    0,(struct sockaddr*)&client_addr,&addr_len);

    printf("No of bytes recvd from client = %d\n",len);

    reset_serialize_buffer(server_send_ser_buffer);
    rpc_server_process_msg(server_recv_ser_buffer,server_send_ser_buffer);
}
    return 0;
}