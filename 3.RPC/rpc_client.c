#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include "config.h"
#include "serialize-deserialize.h"
#include "lst_data.h"

void rpc_send_recv (ser_buff_t *client_send_ser_buffer, 
               ser_buff_t *client_recv_ser_buffer){

    struct sockaddr_in dest;
    int sockfd = 0, rc = 0, recv_size = 0;
    int addr_len;

    dest.sin_family = AF_INET;
    dest.sin_port = htons(SERVER_PORT);
    struct hostent *host = (struct hostent *)gethostbyname(SERVER_IP);
    dest.sin_addr = *((struct in_addr *)host->h_addr_list[0]);
    addr_len = sizeof(struct sockaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd == -1){
        printf("socket creation failed\n");
        return;
    }

    //step 2 : send serialized arguments
    rc = sendto(sockfd, client_send_ser_buffer->b, 
                get_serialize_buffer_length(client_send_ser_buffer), 
                0, (struct sockaddr *)&dest, sizeof(struct sockaddr));

    printf("%s() : %d bytes sent\n", __FUNCTION__, rc);

    //step 8
    recv_size = recvfrom(sockfd, client_recv_ser_buffer->b, 
                get_serialize_buffer_length(client_recv_ser_buffer), 0,
                (struct sockaddr *)&dest, &addr_len);

    printf("%s() : %d bytes recieved\n", __FUNCTION__, recv_size);
}

int lst_sum(lst_data_t* head){

    // step 1 : serialize arguments
    ser_buff_t *client_send_buff = NULL,*client_recv_buffer=NULL;
    init_serialized_buffer_of_defined_size(&client_send_buff,MAX_RECV_SEND_BUFF_SIZE);
    serialize_lst_data_t(head,client_send_buff);

    init_serialized_buffer_of_defined_size(&client_recv_buffer,MAX_RECV_SEND_BUFF_SIZE);

    // step 2-8
    rpc_send_recv(client_send_buff,client_recv_buffer);

    free_ser_buff_t(client_send_buff);
    client_send_buff=NULL;

    // step 9 
    int result =-1;
    de_serialize_data((char*)&result,client_recv_buffer,sizeof(int));

    // step 10
    return result;
}

int main(){
    int num_terms;
    printf("Enter number of elments you want to add in the linked list: ");
    scanf("%d",&num_terms);
    lst_data_t *head=NULL;
    for(int i=1;i<=num_terms;i++){
        int data=-1;
        printf("Enter %d term: ",i);
        scanf("%d",&data);
        push(&head,data);
    }

    int result = lst_sum(head);

    printf("Result of lst_sum: %d\n",result);

}