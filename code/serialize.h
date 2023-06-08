#ifndef _SERIALIZE_
#define _SERIALIZE_

typedef struct serialized_buffer{
    #define SERIALIZE_BUFFER_DEFAULT_SIZE 512
    void *b;
    int size;
    int next;
}ser_buff_t;


// constructor for ser_buff_t
void init_serialized_buffer(ser_buff_t **b);

// serialize and de-serialize functions
void serialize_data(ser_buff_t *b, char *data,int size);
void de_serialize_data(char *dest, ser_buff_t *b,int size);

// other spl functions 
void serialize_buffer_skip(ser_buff_t*b,int skip_size);
void reset_serialize_buffer(ser_buff_t*b);
#endif