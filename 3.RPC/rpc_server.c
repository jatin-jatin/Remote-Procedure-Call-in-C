#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include "config.h"
#include "serialize-deserialize.h"
#include "lst_data.h"

int lst_sum(lst_data_t* head){
    int sum=0;
    while(head!=NULL){
        sum+=head->data;
        head=head->next;
    }
    return sum;
}


int main(){
    int sock_udp_fd = 0, len, addr_len, opt = 1,
        reply_msg_size = 0;
         
	struct sockaddr_in server_addr,
                       client_addr;

    if ((sock_udp_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP )) == -1)
    {
        printf("socket creation failed\n");
        exit(1);
    }

     server_addr.sin_family = AF_INET;
     server_addr.sin_port = htons(SERVER_PORT);
     server_addr.sin_addr.s_addr = INADDR_ANY;
     addr_len = sizeof(struct sockaddr);

	if (setsockopt(sock_udp_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(sock_udp_fd, SOL_SOCKET, SO_REUSEPORT, (char *)&opt, sizeof(opt))<0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

    if (bind(sock_udp_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        printf("socket bind failed\n");
        exit(1);
    }

    ser_buff_t *server_recv_buff=NULL,*server_send_buff=NULL;
    init_serialized_buffer_of_defined_size(&server_recv_buff,MAX_RECV_SEND_BUFF_SIZE);
    init_serialized_buffer_of_defined_size(&server_send_buff,MAX_RECV_SEND_BUFF_SIZE);
    printf("Server ready to service rpc calls\n");

    while(1){
        reset_serialize_buffer(server_recv_buff);
        reset_serialize_buffer(server_send_buff);

        // step 3
        len = recvfrom(sock_udp_fd, server_recv_buff->b, 
                   get_serialize_buffer_length(server_recv_buff),
                   0,(struct sockaddr *)&client_addr, &addr_len);

        printf("No of bytes recvd from client = %d\n",len);

        //step 4
        lst_data_t *head = de_serialize_lst_data_t(server_recv_buff);

        //step 5
        int result = lst_sum(head);

        free_lst_data_t(head); // avoiding memory leak

        // step 6

        serialize_data(server_send_buff,(char*)&result,sizeof(int));

        len = sendto(sock_udp_fd, server_send_buff->b, 
                 get_serialize_buffer_length(server_send_buff),
                 0, (struct sockaddr *)&client_addr, sizeof(struct sockaddr));

        printf("rpc server replied with %d bytes msg\n", len);

    }
    return 0;
}