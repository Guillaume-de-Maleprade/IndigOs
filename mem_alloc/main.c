#include "mem_alloc_list.h"




int main(int argc, char **argv)
{
    createList();

    checkMemory();

    node *n1 = mem_alloc(512);
    node *n2 = mem_alloc(256);
    node *n3 = mem_alloc(1024);
    
    checkMemory();
    
    mem_free(n3);
    
    checkMemory();

    return 0;
}
