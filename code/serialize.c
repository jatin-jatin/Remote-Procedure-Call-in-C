#include "serialize.h"
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<assert.h>

void init_serialized_buffer(ser_buff_t **s_buff){
    *s_buff = (ser_buff_t *)calloc(1,sizeof(ser_buff_t));
    (*s_buff)->b =calloc(1,SERIALIZE_BUFFER_DEFAULT_SIZE);
    (*s_buff)->size = SERIALIZE_BUFFER_DEFAULT_SIZE;
    (*s_buff)->next= 0;
}
void init_serialized_buffer_of_defined_size(ser_buff_t **b, int size){
    (*b) = (ser_buff_t *)calloc(1, sizeof(ser_buff_t));
    (*b)->b = calloc(1, size);
    (*b)->size = size;
    (*b)->next = 0;
}

void serialize_data(ser_buff_t *b, char *data,int size){
    int available_mem = b->size-b->next;
    char isResize=0;

    while(size > available_mem){
        b->size  = b->size*2;
        available_mem = b->size-b->next;
        isResize=1;
    }

    if(isResize){
        b->b = realloc(b->b,b->size);
    }
    memcpy(b->b+b->next,data,size);
    b->next+=size;
}

void de_serialize_data(char *dest, ser_buff_t *b,int size){
    memcpy(dest,b->b+b->next,size);
    b->next+=size;
}

void serialize_buffer_skip(ser_buff_t*b,int skip_size){
    if(b->next + skip_size >=0 && b->next+skip_size < b->size){
        b->next+=skip_size;
    }
}

void reset_serialize_buffer(ser_buff_t*b){
    b->next=0;
}

int get_serialize_buffer_length(ser_buff_t *b){
	return b->size;
}