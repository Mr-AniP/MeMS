// PURPOSE OF THIS FILE IS TO PROVIDE IMLEMENTAION OF MEMORY ALLOCATION AND FREEING FUNCTIONS
#ifndef _MEMSYSCALL_h
#define _MEMSYSCALL_h
#define PAGE_SIZE 4096

// Header files needed
#include <stdio.h> 
#include <stdint.h>
// add files as needed


// conatins impl of systyem calls for memory allocation and freeing (in terms of pagesize)
void *page_allocater(int pages);

void page_free(void *addr, int pages);


#endif