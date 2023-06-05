# Remote-Procedure-Call-in-C
## Introcution
This repository contains a simple remote procedure call implementation in c. 
### What is Remote Procedure call?
* Remote procedure call is mechanism that allows communication between different computing systems.
* Its purpose is to enable a client machine program to execute a procedure or function on a remote server as if it was a local call.

## Components of implementing RPC
* **Serialization and Deserialization**
* **To add**
* **To add**

## Serialization and Deserialization

### What is Serialization ?
Serialization is the process of converting the application state (code in heap) to a flat structure which can be sent over the network. It is
created in such a way that it is independent of the underlying machine.

### What is Deserialization ?
Deserialization is the process of converting the flat structure create using serialization by the sender machine into the original application state in 
the reciever machine. This is done to recreate the original structure in the recieving machine.

### Why do we need serialization and deserialization?
To make the **application state independent of machine, os, compiler, architecture, endianess, etc.**\
We want to convert our application state into a form independent of the above mentioned factors and can be re-created for the specific situation.

![Serialization and Deserialization](https://github.com/jatin-jatin/Remote-Procedure-Call-in-C/blob/main/RPC.png "Serialization and Deserialization")