#include "serialize.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct person_t
{
    char name[30];
    int age;
    int weight;
} person_t;


void serialize_person_t(person_t *obj, ser_buff_t *b){
    if(!obj){
        unsigned int sentinel = 0xFFFFFFFF;
        serialize_data(b,(char*)&sentinel,sizeof(unsigned int));
        return ;
    }

    serialize_data(b,(char*)obj->name,sizeof(char)*30);
    serialize_data(b,(char*)&(obj->age),sizeof(int));
    serialize_data(b,(char*)&(obj->weight),sizeof(int));

}

person_t* de_serialize_person_t(ser_buff_t *b){
    unsigned int sentinel=0;
    de_serialize_data((char*)&sentinel,b,sizeof(unsigned int));
    if(sentinel==0xFFFFFFFF){
        return NULL;
    }
    serialize_buffer_skip(b,-1*(int)(sizeof(unsigned int)));

    person_t *obj = calloc(1,sizeof(person_t));
    de_serialize_data((char*)obj->name,b,sizeof(char)*30);
    de_serialize_data((char*)&obj->age,b,sizeof(int));
    de_serialize_data((char*)&obj->weight,b,sizeof(int));
    return obj;
}

int main(){
    ser_buff_t *buff1;
    init_serialized_buffer(&buff1);

    person_t *person1 = calloc(1,sizeof(person_t));
    if(person1!=NULL){
        strcpy(person1->name,"jatinlachhwani");
        person1->age=23;
        person1->weight = 73;  // Assign a value to person1->weight
    }
    serialize_person_t(person1,buff1);
    reset_serialize_buffer(buff1);
    person_t *person2 = de_serialize_person_t(buff1);
    printf("%s:%d:%d\n",person2->name,person2->age,person2->weight);
    printf("%s:%d:%d\n",person1->name,person1->age,person1->weight);

    free(person1);
    free(buff1);

    return 0;
}
