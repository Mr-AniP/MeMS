#include "mainimpl.h"
// implementation of mems.h functions

ProcessChain* MEMORY_HEAD;
MainChain* FREE_HEAD ;

void my_mem_init(void){
    freehead=NULL;
    memoryhead=NULL;
}

void *my_mem_alloc(size_t size){}
void my_mem_free(void *ptr){}

