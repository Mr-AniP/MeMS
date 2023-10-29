#include<stdlib.h>
#include "FreeList.h"

void insert_MainNode(MainChain **root,SideChain *node,int pages){
    if((*root)==NULL){
        *root=(MainChain*)malloc(sizeof(MainChain));
        (*root)->next=NULL;
        (*root)->prev=NULL;
        (*root)->sideChain=*node;
        (*root)->pages=pages;
        return;
    }
    MainChain *temp=(*root)->prev,*new=*root=(MainChain*)malloc(sizeof(MainChain));
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
        free(*root);
        *root=NULL;
        return;
    }
    MainChain *temp=(*root)->prev;
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

void delete_SideNode(SideChain **root){
    if((*root)==NULL){
        return;
    }
    if((*root)->prev==NULL){
        free(*root);
        *root=NULL;
        return;
    }
    SideChain *temp=(*root)->prev;
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

void insert_SideNode(SideChain **root,Freestatus status,int size){
    if((*root)==NULL){
        *root=(SideChain*)malloc(sizeof(SideChain));
        (*root)->next=NULL;
        (*root)->prev=NULL;
        (*root)->status=status;
        (*root)->size=size;
        return;
    }
    SideChain *temp=(*root)->prev,*new=*root=(SideChain*)malloc(sizeof(SideChain));
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