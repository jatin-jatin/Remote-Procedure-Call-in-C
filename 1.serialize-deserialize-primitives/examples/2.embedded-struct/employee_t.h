#pragma once
#include "./../../serialize-deserialize.h"

typedef struct employee_t 
{ 
    int id;
    char first_name[30];
    char last_name[30];
}employee_t;

void serialize_employee_t(employee_t*obj,ser_buff_t*b);
employee_t* de_serialize_employee_t(ser_buff_t *b);
void display_employee_t(employee_t *emp);