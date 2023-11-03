#ifndef _MAINIMPL_h
#define _MAINIMPL_h
#include "memsyscall.h"

// decleration of my_mem_alloc and my_mem_free functions
void *my_mem_alloc(size_t size);
void my_mem_free(void *ptr);



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


void insert_MainNode(MainChain **root,SideChain *node,int pages){
    if((*root)==NULL){
        *root=(MainChain*)my_mem_alloc(sizeof(MainChain));
        (*root)->next=NULL;
        (*root)->prev=NULL;
        (*root)->sideChain=*node;
        (*root)->pages=pages;
        return;
    }
    MainChain *temp=(*root)->prev,*new=*root=(MainChain*)my_mem_alloc(sizeof(MainChain));
    new->sideChain=*node;
    new->pages=pages;
    new->next=*root;
    (*root)->prev=new;
    if(temp==NULL){
        (*root)->next=new;
        new->prev=*root;
    }
    else{
        temp->next=new;
        new->prev=temp;
    }
}

void delete_MainNode(MainChain **root){
    if((*root)==NULL){
        return;
    }
    if((*root)->prev==NULL){
        my_mem_free(*root);
        *root=NULL;
        return;
    }
    MainChain *temp=(*root)->prev;
    if(temp==(*root)->next){
        my_mem_free(*root);
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

void delete_SideNode(SideChain **root){
    if((*root)==NULL){
        return;
    }
    if((*root)->prev==NULL){
        my_mem_free(*root);
        *root=NULL;
        return;
    }
    SideChain *temp=(*root)->prev;
    if(temp==(*root)->next){
        my_mem_free(*root);
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

void insert_SideNode(SideChain **root,Freestatus status,int size){
    if((*root)==NULL){
        *root=(SideChain*)my_mem_alloc(sizeof(SideChain));
        (*root)->next=NULL;
        (*root)->prev=NULL;
        (*root)->status=status;
        (*root)->size=size;
        return;
    }
    SideChain *temp=(*root)->prev,*new=*root=(SideChain*)my_mem_alloc(sizeof(SideChain));
    new->status=status;
    new->size=size;
    new->next=*root;
    (*root)->prev=new;
    if(temp==NULL){
        (*root)->next=new;
        new->prev=*root;
    }
    else{
        temp->next=new;
        new->prev=temp;
    }
}





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

//decleration of som e important functions
void my_mem_init(void);

#endif