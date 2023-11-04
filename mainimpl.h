// Purpose of this file is to provide mainline implementation for mems.h to work

#ifndef _MAINIMPL_h
#define _MAINIMPL_h
#include "freelist.h"

// decleration of my_mem_alloc and my_mem_free functions
void * my_mem_alloc(size_t size);
void my_mem_free(void *ptr);
//decleration of some important functions
void my_mem_init(void);
void mem_dealloc(void);
void free_list_info(void);
void * my_mem_to_physical_addr(void *v_ptr);

/*
// implementation of memmory map (structure to store the information of the process)
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


void insert_Process(ProcessChain **root,MemoryChain *node,int id){
    if((*root)==NULL){
        (*root)=(ProcessChain *)my_mem_alloc(sizeof(ProcessChain));
        (*root)->id=id;
        (*root)->next=NULL;
        (*root)->memory=node;
        return;
    }
    ProcessChain *temp=(*root);
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=(ProcessChain *)my_mem_alloc(sizeof(ProcessChain));
    temp->next->id=id;
    temp->next->next=NULL;
    temp->next->memory=node;
}

void delete_Process(ProcessChain **root){
    if((*root)==NULL){
        return;
    }
    ProcessChain *temp=(*root);
    (*root)=(*root)->next;
    my_mem_free(temp);
}

void insert_memoryNode(MemoryChain **root,int virtualmax,int virtualmin,int physicalmax,int physicalmin){
    if((*root)==NULL){
        (*root)=(MemoryChain *)my_mem_alloc(sizeof(MemoryChain));
        (*root)->virtualmax=virtualmax;
        (*root)->virtualmin=virtualmin;
        (*root)->physicalmax=physicalmax;
        (*root)->physicalmin=physicalmin;
        (*root)->next=NULL;
        (*root)->prev=NULL;
        return;
    }
    MemoryChain head=(*root)->prev,*temp=(MemoryChain *)my_mem_alloc(sizeof(MemoryChain));
    temp->virtualmax=virtualmax;
    temp->virtualmin=virtualmin;
    temp->physicalmax=physicalmax;
    temp->physicalmin=physicalmin;
    temp->next=*root;
    (*root)->prev=temp;
    if(head==NULL){
        (*root)->next=temp;
        temp->prev=*root;
    }
    else{
        head->next=temp;
        temp->prev=head;
    }
}
void delete_memoryNode(MemoryChain **root){
    if(*root==NULL){
        return;
    }
    if((*root)->prev==NULL){
        my_mem_free(*root);
        *root=NULL;
        return;
    }
    MemoryChain *temp=(*root)->prev;
    if(temp==(*root)->next){
        frmy_mem_freeee(*root);
        temp->prev=NULL;
        temp->next=NULL;
        *root=temp;
        return;
    }
    temp->next=(*root)->next;
    (*root)->next->prev=temp;
    my_mem_free(*root);
    *root=temp;
}

*/

#endif