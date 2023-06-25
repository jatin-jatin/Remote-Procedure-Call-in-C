#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./../../serialize-deserialize.h"
#include "employee_t.h"


typedef struct employee_performance_t
{
    char company_name[30];
    employee_t *emp;
    int rating;
}employee_performance_t;

void serialize_employee_performance_t(employee_performance_t *obj, ser_buff_t*b){
    // filling spl value for NULL
    if(obj==NULL){
        unsigned int sentinel = 0xFFFFFFFF;
        serialize_data(b,(char*)&sentinel,sizeof(unsigned int));
        return;
    }
    // if not null fill the buffer with struct data
    serialize_data(b,(char*)obj->company_name,sizeof(char)*30);

    // notice the call to serialize nested struct
    serialize_employee_t(obj->emp,b); 

    serialize_data(b,(char*)&obj->rating,sizeof(int));
}

employee_performance_t* de_serialize_employee_performance_t(ser_buff_t*b){
    // check for null
    unsigned int sentinel=0;
    de_serialize_data((char*)&sentinel,b,sizeof(unsigned int));
    if(sentinel==0xFFFFFFFF)
        return NULL;
        
    // if not null rewind read point in buffer
    serialize_buffer_skip(b,(int)sizeof(unsigned int)*-1);

    // fill the struct from serialized data
    employee_performance_t* obj = calloc(1,sizeof(employee_performance_t));
    de_serialize_data((char*)obj->company_name,b,30*sizeof(char));
    obj->emp=de_serialize_employee_t(b);
    de_serialize_data((char*)&obj->rating,b,sizeof(int));
    return obj;
}

void display_employee_performance_t(employee_performance_t *obj){
    printf("%s\n",obj->company_name);
    display_employee_t(obj->emp);
    printf("%d\n",obj->rating);
}

int main(){
    employee_t *emp1 = calloc(1,sizeof(employee_t));
    emp1->id = 99;
    strcpy(emp1->first_name,"israel");
    strcpy(emp1->last_name,"adesanya");

    employee_performance_t *emp_rate1;
    emp_rate1 = calloc(1,sizeof(employee_performance_t));
    strcpy(emp_rate1->company_name,"ufc");
    emp_rate1->emp=emp1;
    emp_rate1->rating=10;
    
    ser_buff_t *buff;
    init_serialized_buffer(&buff);

    serialize_employee_performance_t(emp_rate1,buff);
    reset_serialize_buffer(buff);
    employee_performance_t *emp_rate2= de_serialize_employee_performance_t(buff);

    printf("Serialized Structure\n");
    display_employee_performance_t(emp_rate1);
    printf("----------------------------------------------------------\n");
    printf("Deserialized Structure\n");
    display_employee_performance_t(emp_rate2);

    free(emp_rate1);
    free(emp_rate2);

    return 0;
}