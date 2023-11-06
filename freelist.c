#include "freelist.h"

void insert_MainNode(MainChain **root,int pages){
    if((*root)==NULL){
        *root=(MainChain *)(char*)(page_allocater(pages));
        (*root)->next=(*root);
        (*root)->prev=(*root);
        (*root)->pages=pages;
        (*root)->side_chain=(SideChain*)((char*)(*root) + sizeof(MainChain));
        (*root)->side_chain->status=HOLE;
        (*root)->side_chain->size=(pages*PAGE_SIZE)-sizeof(MainChain)-sizeof(SideChain);
        (*root)->side_chain->next=(*root)->side_chain;
        (*root)->side_chain->prev=(*root)->side_chain;
        return;
    }
    MainChain *temp=(*root)->prev,*newnode=(MainChain*)(char*)(page_allocater(pages));
    newnode->pages=pages;
    newnode->next=*root;
    (*root)->prev=newnode;
    if(temp==(*root)){
        (*root)->next=newnode;
        newnode->prev=*root;
    }
    else{
        temp->next=newnode;
        newnode->prev=temp;
    }
    newnode->side_chain=(SideChain*)((char*)newnode + sizeof(MainChain));
    newnode->side_chain->status=HOLE;
    newnode->side_chain->size=(pages*PAGE_SIZE)-sizeof(MainChain)-sizeof(SideChain);
    newnode->side_chain->next=newnode->side_chain;
    newnode->side_chain->prev=newnode->side_chain;
}

void delete_MainNode(MainChain **root){
    if((*root)==NULL){
        return;
    }
    if((*root)->prev==NULL){
       page_free((void*)(char*)(*root), (*root)->pages);
        *root=NULL;
        return;
    }
    MainChain *temp=(*root)->prev;
    if(temp==(*root)->next){
        page_free((void*)(char*)(*root), (*root)->pages);
        temp->prev=NULL;
        temp->next=NULL;
        *root=temp;
        return;
    }
    temp->next=(*root)->next;
    (*root)->next->prev=temp;
    page_free((void*)(char*)(*root), (*root)->pages);
    *root=temp;
}

// void delete_SideNode(SideChain **root){
//     if((*root)==NULL){
//         return;
//     }
//     if((*root)->prev==NULL){
//         my_mem_free(*root);
//         *root=NULL;
//         return;
//     }
//     SideChain *temp=(*root)->prev;
//     if(temp==(*root)->next){
//         my_mem_free(*root);
//         temp->prev=NULL;
//         temp->next=NULL;
//         *root=temp;
//         return;
//     }
//     temp->next=(*root)->next;
//     (*root)->next->prev=temp;
//     my_mem_free(*root);
//     *root=temp;
// }

void insert_SideNode(SideChain *current,int size,int sz1){
    if(current==NULL){
        printf("ERROR :: Current Block is NULL\n");
        return;
    }
    SideChain *newnode=(SideChain*) ((char*)current + sizeof(SideChain) + size +sz1);
    newnode->status=HOLE;
    newnode->size=current->size-size-sizeof(SideChain)-sz1;
    newnode->next=current->next;
    newnode->prev=current;
    current->next=newnode;
    newnode->next->prev=newnode;
    current->size=size;
}

int try_merge(SideChain **node){
    if((*node)->status!=HOLE){
        return 0;
    }
    if((*node)->prev<(*node) && (*node)->prev->status==HOLE){
        (*node)->prev->size+=(*node)->size+sizeof(SideChain);
        (*node)->prev->next=(*node)->next;
        (*node)->next->prev=(*node)->prev;
        (*node)=(*node)->prev;
        return 1;
    }
    if((*node)->next>(*node) &&(*node)->next->status==HOLE){
        (*node)->size+=(*node)->next->size+sizeof(SideChain);
        (*node)->next->next->prev=(*node);
        (*node)->next=(*node)->next->next;
        return 1;
    }
    return 0;
}