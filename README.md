# Remote-Procedure-Call-in-C
## Introcution
This repository contains a simple remote procedure call implementation in c. 
### What is Remote Procedure call?
* Remote procedure call is mechanism that allows communication between different computing systems.
* Its purpose is to enable a client machine program to execute a procedure or function on a remote server as if it was a local call.

## Components of implementing RPC
* **Serialization and Deserialization**
* **Socket programming**
* **To add**

## Serialization and Deserialization

### What is Serialization ?
Serialization is the process of converting a memory object to a flat structure which can be sent over the network. It is
created in such a way that it is independent of the underlying machine.
![Serialization](https://github.com/jatin-jatin/Remote-Procedure-Call-in-C/blob/main/.pictures/serialization.png "Serialization")

### What is Deserialization ?
Deserialization is the process of converting the  serialized flat structure cr original application state in 
the reciever machine. This is done to recreate the original structure in the recieving machine.
![Deserialization](https://github.com/jatin-jatin/Remote-Procedure-Call-in-C/blob/main/.pictures/deserialization.png "Deserialization")

### Why do we need serialization and deserialization?
To make the **application state independent of machine, os, compiler, architecture, endianess, etc.**\
We want to convert our application state into a form independent of the above mentioned factors and can be re-created for the specific situation.

### Examples of Serialization and Deserialization

#### 1. Simple Struct: [link](serialize-deserialize-primitives/examples/1.simple-struct/simple-struct.c)
```
typedef struct employee_t 
{ 
    // only primitive types
    int id;
    char first_name[30];
    char last_name[30];
}employee_t;
```
#### 2. Embedded Struct: [link](serialize-deserialize-primitives/examples/2.embedded-struct/embedded-struct.c)
```
typedef struct company_t
{
    char name[30];
    employee_t CEO; // embedded employee_t struct
    int valuation;
    int start_year;
}company_t;
```
#### 3. Nested Struct: [link](serialize-deserialize-primitives/examples/3.nested-struct/nested-struct.c)
```
typedef struct employee_performance_t
{
    char company_name[30];
    employee_t *emp; // nested struct
    int rating;
}employee_performance_t;
```