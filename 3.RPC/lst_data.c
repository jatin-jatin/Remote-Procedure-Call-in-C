#include<stdlib.h>
#include"lst_data.h"
#include<stdio.h>

void serialize_lst_data_t(lst_data_t *obj,ser_buff_t *b){
    // filling spl value for NULL
    if(obj==NULL){
        unsigned int sentinel = 0xFFFFFFFF;
        serialize_data(b,(char*)&sentinel,sizeof(unsigned int));
        return;
    }
    serialize_data(b,(char*)(&obj->data),sizeof(int));
    serialize_lst_data_t(obj->next,b);
}

lst_data_t* de_serialize_lst_data_t(ser_buff_t *b){
    // check for null
    unsigned int sentinel=0;
    de_serialize_data((char*)&sentinel,b,sizeof(unsigned int));
    if(sentinel==0xFFFFFFFF)
        return NULL;
        
    // if not null rewind read point in buffer
    serialize_buffer_skip(b,(int)sizeof(unsigned int)*-1);

    lst_data_t *obj = calloc(1,sizeof(lst_data_t));
    de_serialize_data((char*)&obj->data,b,sizeof(int));
    obj->next = de_serialize_lst_data_t(b);
    return obj;
}

void push(lst_data_t **head_ptr,int element){
    lst_data_t *new_node= (lst_data_t *)malloc(sizeof(lst_data_t));

    // set data and new ptr to current head
    new_node->data=element;
    new_node->next=*head_ptr;

    // current head points to new_node
    *head_ptr=new_node;
}

void print_lst_data(lst_data_t* head){
    while(head!=NULL){
        printf("%d ",head->data);
        head=head->next;
    }printf("/n");
}

void free_lst_data_t(lst_data_t* head){
    while(head!=NULL){
        lst_data_t*temp=head;
        head=head->next;
        free(temp);
    }
}