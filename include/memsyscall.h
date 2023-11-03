#ifndef _MEMSYSCALL_h
#define _MEMSYSCALL_h
#include <stdio.h>
void * my_mem_alloc( size_t size );
void my_mem_free( void * ptr );
#endif