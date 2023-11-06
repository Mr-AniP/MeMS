// Purpose of this file is to provide mainline implementation for mems.h to work

#ifndef _MAINIMPL_h
#define _MAINIMPL_h
#include "freelist.h"
#include"memorymap.h"

// decleration of my_mem_alloc and my_mem_free functions
void * my_mem_alloc(size_t size);
void my_mem_free(void *ptr);
//decleration of some important functions
void my_mem_init(void);
void mem_dealloc(void);
void free_list_info(void);
void * my_mem_to_physical_addr(void *v_ptr);

#endif