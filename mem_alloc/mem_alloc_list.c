// TODO
#include "mem_alloc_list.h"
#include <assert.h>

node *start;

void createList()
{

    start = malloc((size_m)(MEM_SIZE));/* Use of malloc to get the first available address with enough space for the test with MEM_SIZE
    (when using on windows, otherwise, give the first available address (like (void*)0x000F00))*/

    start->addr = start;
    start->addr+=16; // increment of the addr attribute of the node 16, because 16 bytes are necessary to store the node itself
    start->next = MY_NULL; 
    start->size = (size_m)(MEM_SIZE);
    start->allocated = false;  

};

node *checkMemFree(size_m p_size)
{
    node *c_ptr = start;
    node *smaller_ptr;
    smaller_ptr = MY_NULL;
    size_m size = p_size + 16;

    size_m free_mem = 0;
    while (c_ptr != MY_NULL)
    {
        if (!c_ptr->allocated)
        {
            if (c_ptr->size == size)
            {
                return c_ptr;
            }
            if (c_ptr->size > size)
            {
                if (free_mem == 0)
                {
                    free_mem = c_ptr->size;
                    smaller_ptr = c_ptr;
                }
                else if (c_ptr->size < free_mem)
                {
                    free_mem = c_ptr->size;
                    smaller_ptr = c_ptr;
                }
            }
        }
        c_ptr = c_ptr->next;
    }
    return smaller_ptr;
};

node *combineFreeNodes()
{
    node *currentNode = start;
    int i = 0;
    int j = 0;
    int k = 0;
    while(currentNode != MY_NULL && currentNode->next != MY_NULL){
        if(currentNode->next != MY_NULL){
            if(currentNode->allocated == false && currentNode->next->allocated == false){
                currentNode->size += currentNode->next->size;// + 16;
                currentNode->next = currentNode->next->next;
            }
        }
        currentNode = currentNode->next;
    }
};

node *allocate(void *address, size_m size)
{
    if(address == MY_NULL) return MY_NULL;

    node *toDivide = address;
    toDivide->size = toDivide->size - size - 16; //because 16 bytes are necessary to store the node itself
    node *newNode = (void*)((int)address + size);
    newNode->size = size;
    newNode->addr = newNode;
    newNode->addr+= 16; //increment of the addr attribute of the node 16, because 16 bytes are necessary to store the node itself
    newNode->next = toDivide->next;
    newNode->allocated = true;
    toDivide->next = newNode;
    return newNode;
};

void mem_free(void *address){
    node *toFree = (void *)(address-16);
    toFree->allocated = false;
    combineFreeNodes();
};

void *mem_alloc(size_m size)
{
    node *tmp = checkMemFree(size);
    if (tmp != MY_NULL)
    {
        node *allocated = allocate(tmp, size);
        printf("Allocation: \naddress: %p \nallocated: %d \nsize: %d\n\n\n", allocated->addr, allocated->allocated, allocated->size);

        return allocated->addr;
    }
    printf("Not enough space available!\n");
    return MY_NULL;
};


void checkMemory(){
    node *currentNode = start;
    int i = 1;
    while(currentNode != MY_NULL){
        printf("Node number %d : \naddress: %p \nallocated: %d \nsize: %d\n\n\n", i, currentNode->addr, currentNode->allocated, currentNode->size);
        currentNode = currentNode->next;
        i++;
    }
}
