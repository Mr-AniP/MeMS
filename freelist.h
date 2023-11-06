#ifndef _FREELIST_h
#define _FREELIST_h
#include "memsyscall.h"

// implementaion of freeList
enum free_or_not{
    HOLE,
    PROCESS
};

struct sidenode
{
    enum free_or_not status;
    int size;
    struct sidenode *next;
    struct sidenode *prev;
}; 

struct MainNode
{   int pages;
    struct sidenode *side_chain;
    struct MainNode *next;
    struct MainNode *prev;
};

typedef struct MainNode MainChain;
typedef struct sidenode SideChain;
typedef enum free_or_not Freestatus;


// Important usefull functions
void insert_MainNode(MainChain **root,int pages);
void delete_MainNode(MainChain **root);
void insert_SideNode(SideChain *current,int size,int sz1);
int try_merge(SideChain **node);
// void delete_SideNode(SideChain **root);

#endif