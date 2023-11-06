// memmap imlementation
#include "memorymap.h"
void insert_Process(ProcessChain **root,void *node,void* mem,uintptr_t vmax, uintptr_t vmin){
    if((*root)==NULL){
        (*root)=(ProcessChain *)node;
        (*root)->next=NULL;
        (*root)->phys_addr=mem;
        (*root)->virt_max=vmax;
        (*root)->virt_min=vmin;
        return;
    }
    ProcessChain *newnode=(ProcessChain *)node;
    newnode->next=NULL;
    newnode->phys_addr=mem;
    newnode->virt_max=vmax;
    newnode->virt_min=vmin;
    //find a suitable place to insert
    ProcessChain *temp=(*root);
    while(temp->next!=NULL){
        if(temp->next->virt_min > newnode->virt_max){
            break;
        }
        temp=temp->next;
    }
    if(temp->virt_max < newnode->virt_min){
        newnode->next=temp->next;
        temp->next=newnode;
    }
    else{
        fprintf(stderr,"Error: Overlapping of memory\n");
        exit(1);
    }
}

void delete_Process(ProcessChain **root,ProcessChain *node){
    if((*root)==NULL){
        return;
    }
    if((*root)==node){
        (*root)=(*root)->next;
        return;
    }
    ProcessChain *temp=(*root);
    while(temp!=NULL){
        if(temp->next==node){
            temp->next=temp->next->next;
            return;
        }
        temp=temp->next;
    }
}