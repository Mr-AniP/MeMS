#ifndef _FREELIST_h
#define _FREELIST_h
#include "memsyscall.h"

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

void insert_MainNode(MainChain **root,SideChain *node,int pages);
void delete_MainNode(MainChain **root);
void insert_SideNode(SideChain **root,Freestatus status,int size);
void delete_SideNode(SideChain **root);
#endif