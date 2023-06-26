#pragma once
#include"serialize-deserialize.h"
typedef struct lst_data_t{
    int data;
    struct lst_data_t* next;
}lst_data_t;

void serialize_lst_data_t(lst_data_t *obj,ser_buff_t *b);
lst_data_t* de_serialize_lst_data_t(ser_buff_t *b);
void push(lst_data_t **head_ptr,int element);
void print_lst_data_t(lst_data_t* head);
void free_lst_data_t(lst_data_t* head);