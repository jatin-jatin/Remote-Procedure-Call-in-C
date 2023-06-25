#include<stdlib.h>
#include<stdio.h>
#include "./../../serialize-deserialize.h"

typedef struct employee_t 
{ 
    int id;
    char first_name[30];
    char last_name[30];
}employee_t;

void serialize_employee_t(employee_t*obj,ser_buff_t*b){
    // returning spl value for NULL
    if(obj==NULL){
        unsigned int sentinel = 0xFFFFFFFF;
        serialize_data(b,(char*)&sentinel,sizeof(unsigned int));
        return;
    }
    // if not null fill the buffer with struct data
        serialize_data(b,(char*)&obj->id,sizeof(int));
        serialize_data(b,(char*)obj->first_name,sizeof(char)*30);
        serialize_data(b,(char*)obj->last_name,sizeof(char)*30);
}

employee_t* de_serialize_employee_t(ser_buff_t *b){
    // check for null
    unsigned int sentinel=0;
    de_serialize_data((char*)&sentinel,b,sizeof(unsigned int));
    if(sentinel==0xFFFFFFFF)
        return NULL;
        
    // if not null rewind read point in buffer
    serialize_buffer_skip(b,(int)sizeof(unsigned int)*-1);

    // fill the struct from serialized data
    employee_t * obj = calloc(1,sizeof(employee_t));
    de_serialize_data((char*)&obj->id,b,sizeof(int));
    de_serialize_data((char*)obj->first_name,b,30*sizeof(char));
    de_serialize_data((char*)obj->last_name,b,30*sizeof(char));
    return obj;
}

void display_employee_t(employee_t *emp){
    printf("Employee ID: %d\n", emp->id);
    printf("First Name: %s\n", emp->first_name);
    printf("Last Name: %s\n", emp->last_name);
}