#ifndef MEM_ALLOC
#define MEM_ALLOC

#define MY_NULL ((void *)0) //x00300000)
#define ADDR_START ((void *)0x00300010)

#define MEM_SIZE (4096)// * 1024) // * 1024)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct node node;
typedef struct list list;
typedef uint32_t size_m;
typedef uint8_t byte;

typedef enum
{
    false,
    true
} bool;

struct node //16bytes
{
    node *next; //4bytes
    size_m size; //4bytes
    void *addr; //4bytes
    bool allocated; //4bytes (0/1)
};

void createList(); // Initialize the list of memory nodes

node *checkMemFree(size_m); // Return MY_NULL if there is not enough free space available, otherwise returns the address of the free space available

node *allocate(void *, size_m); // if there is enough space, creates an allocated node with given address and size, and a possible unallocated node for the remaining free space

node *combineFreeNodes(); // If thee is consecutive free nodes, combines them together

void mem_free(void *); // free the given address and call the combine function

void *mem_alloc(size_m); // checkMemFree(size), allocate(free, size)

void checkMemory(); // Go through the memory list and shows relevant info

#endif
