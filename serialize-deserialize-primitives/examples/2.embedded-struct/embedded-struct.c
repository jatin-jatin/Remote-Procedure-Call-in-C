#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./../../serialize-deserialize.h"
#include "employee_t.h"


typedef struct company_t
{
    char name[30];
    employee_t CEO;
    int valuation;
    int start_year;
}company_t;

void serialize_company_t(company_t *obj, ser_buff_t*b){
    // returning spl value for NULL
    if(obj==NULL){
        unsigned int sentinel = 0xFFFFFFFF;
        serialize_data(b,(char*)&sentinel,sizeof(unsigned int));
        return;
    }
    // if not null fill the buffer with struct data
    serialize_data(b,(char*)obj->name,sizeof(char)*30);

    // notice the call to serialize embedded struct
    serialize_employee_t(&obj->CEO,b); 

    serialize_data(b,(char*)&obj->valuation,sizeof(int));
    serialize_data(b,(char*)&obj->start_year,sizeof(int));
}

company_t* de_serialize_company_t(ser_buff_t*b){
    // check for null
    unsigned int sentinel=0;
    de_serialize_data((char*)&sentinel,b,sizeof(unsigned int));
    if(sentinel==0xFFFFFFFF)
        return NULL;
        
    // if not null rewind read point in buffer
    serialize_buffer_skip(b,(int)sizeof(unsigned int)*-1);

    // fill the struct from serialized data
    company_t* obj = calloc(1,sizeof(company_t));
    de_serialize_data((char*)obj->name,b,30*sizeof(char));
    employee_t *emp = de_serialize_employee_t(b);
    obj->CEO=*emp;
    free(emp);
    de_serialize_data((char*)&obj->valuation,b,sizeof(int));
    de_serialize_data((char*)&obj->start_year,b,sizeof(int));
    return obj;
}

void display_company_t(company_t *obj){
    printf("%s\n",obj->name);
    display_employee_t(&obj->CEO);
    printf("%d\n",obj->valuation);
    printf("%d\n",obj->start_year);
}

int main(){
    company_t *comp1=calloc(1,sizeof(company_t));
    strcpy(comp1->name,"Meta");
    comp1->CEO.id=1001;
    strcpy(comp1->CEO.first_name,"Mark");
    strcpy(comp1->CEO.last_name,"Zuckerberg");
    comp1->valuation=100000001;
    comp1->start_year = 2004;

    ser_buff_t *buff;
    init_serialized_buffer(&buff);

    serialize_company_t(comp1,buff);
    reset_serialize_buffer(buff);
    company_t *comp2 = de_serialize_company_t(buff);

    display_company_t(comp1);
    display_company_t(comp2);

    free(comp1);
    free(comp2);
    return 0;
}