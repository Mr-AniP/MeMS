#ifndef _MEMMORYMAP_h
#define _MEMMORYMAP_h
#include "memsyscall.h"

struct Node{   
    int virtualmax;
    int virtualmin;
    int physicalmax;
    int physicalmin;
    struct Node *next;
    struct Node *prev;
};

struct nodeproc{
    int pid;
    struct Node *memoryhead;
    struct nodeproc *next;
};

typedef struct Node MemoryChain;
typedef struct nodeproc ProcessChain;

void insert_Process(ProcessChain **root,MemoryChain *node,int id);
void delete_Process(ProcessChain **root);
void insert_memoryNode(MemoryChain **root,int virtualmax,int virtualmin,int physicalmax,int physicalmin);
void delete_memoryNode(MemoryChain **root);

#endif