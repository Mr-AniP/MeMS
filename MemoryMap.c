
#include<stdlib.h>
#include "MemoryMap.h"

void insert_Process(ProcessChain **root,MemoryChain *node,int id){
    if((*root)==NULL){
        (*root)=(ProcessChain *)malloc(sizeof(ProcessChain));
        (*root)->id=id;
        (*root)->next=NULL;
        (*root)->memory=node;
        return;
    }
    ProcessChain *temp=(*root);
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=(ProcessChain *)malloc(sizeof(ProcessChain));
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
    free(temp);
}

void insert_memoryNode(MemoryChain **root,int virtualmax,int virtualmin,int physicalmax,int physicalmin){
    if((*root)==NULL){
        (*root)=(MemoryChain *)malloc(sizeof(MemoryChain));
        (*root)->virtualmax=virtualmax;
        (*root)->virtualmin=virtualmin;
        (*root)->physicalmax=physicalmax;
        (*root)->physicalmin=physicalmin;
        (*root)->next=NULL;
        (*root)->prev=NULL;
        return;
    }
    MemoryChain head=(*root)->prev,*temp=(MemoryChain *)malloc(sizeof(MemoryChain));
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
        free(*root);
        *root=NULL;
        return;
    }
    MemoryChain *temp=(*root)->prev;
    if(temp==(*root)->next){
        free(*root);
        temp->prev=NULL;
        temp->next=NULL;
        *root=temp;
        return;
    }
    temp->next=(*root)->next;
    (*root)->next->prev=temp;
    free(*root);
    *root=temp;
}