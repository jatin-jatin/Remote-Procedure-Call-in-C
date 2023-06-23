#include "serialize.h"
#include<stdlib.h>


typedef struct person_t{
    char name[30];
    int age;
    occupation_t *occ;
    int weight;
}person_t;

typedef struct  occupation_t
{
    char dept_name[30];
    int emp_code;
}occupation_t;

void serialize_occupation_t(occupation_t *obj,ser_buff_t *b){
    if(!obj){
        unsigned int sentinel = 0xFFFFFFFF;
        serialize_data(b,(char*)&sentinel,sizeof(unsigned int));
        return ;
    }
    serialize_data(b,(char*)obj->dept_name,30*sizeof(char));
    serialize_data(b,(char*)(&obj->emp_code),sizeof(int));
}

void serialize_persont_t(person_t *obj,ser_buff_t *b){
    if(!obj){
        unsigned int sentinel = 0xFFFFFFFF;
        serialize_data(b,(char*)&sentinel,sizeof(unsigned int));
        return ;
    }

    serialize_data(b,(char*)obj->name,30*sizeof(char));
    serialize_data(b,(char*)(&obj->age),sizeof(int));
    serialize_occupation_t(obj->occ,b);
    serialize_data(b,(char*)(&obj->weight),sizeof(int));

}

occupation_t* de_serialize_occupation_t(ser_buff_t *b){
    unsigned int sentinel=0;
    de_serialize_data((char*)(&sentinel),b,sizeof(unsigned int));
    if(sentinel==0xFFFFFFFF){
        return NULL;
    }
    serialize_buffer_skip(b,-1*sizeof(unsigned int));

    occupation_t* obj = calloc(sizeof(occupation_t),1);

    de_serialize_data((char*)(obj->dept_name),b,sizeof(char)*30);
    de_serialize_data((char*)&(obj->emp_code),b,sizeof(int));
    return obj;
}

person_t* de_serialize_person_t(ser_buff_t *b){
    unsigned int sentinel=0;
    de_serialize_data((char*)(&sentinel),b,sizeof(unsigned int));
    if(sentinel==0xFFFFFFFF){
        return NULL;
    }
    serialize_buffer_skip(b,-1*sizeof(unsigned int));

    person_t *obj = calloc(1,sizeof(person_t));
    de_serialize_data((char*)obj->name,b,sizeof(char)*30);
    de_serialize_data((char*)&(obj->age),b,sizeof(int));
    obj->occ = de_serialize_occupation_t(b);
    de_serialize_data((char*)&(obj->weight),b,sizeof(int));
    return obj;
}


int main(){
    ser_buff_t *b=NULL;
    init_serialized_buffer(&b);
}
