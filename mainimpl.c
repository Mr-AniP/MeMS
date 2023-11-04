#include "mainimpl.h"
// implementation of mems.h functions

MainChain* FREE_HEAD ;
// ProcessChain* MEMORY_HEAD;
void my_mem_init(void){
    FREE_HEAD=NULL;
    // MEMORY_HEAD=NULL;
}


void *my_mem_alloc(size_t size){
    MainChain* temp=FREE_HEAD;
    SideChain* temp2=NULL;
    do{
        if(temp!=NULL){
            temp2=temp->side_chain;
            do{
                if(temp2!=NULL){
                    if(temp2->status==HOLE && temp2->size>=size){
                        if(temp2->size > size + sizeof(SideChain)){
                            insert_SideNode(temp2,size);
                        }
                        temp2->status=PROCESS;
                        return (void*)((char*)temp2 + sizeof(SideChain));
                    }
                    temp2=temp2->next;
                }
            }while(temp2!=temp->side_chain);
            temp=temp->next;
        }
    }while(temp!=FREE_HEAD);
    insert_MainNode(&FREE_HEAD,1+((int)size/PAGE_SIZE));
    temp2=FREE_HEAD->prev->side_chain;
    if(temp2->size > size + sizeof(SideChain)){
        insert_SideNode(temp2,size);
    }
    temp2->status=PROCESS;
    return (void*)((char*)temp2 + sizeof(SideChain));
}

void my_mem_free(void *ptr){
    SideChain* node= (SideChain*)((char*)ptr -sizeof(SideChain));
    node->status=HOLE;
    while(try_merge(&node)!=0);
}


void mem_dealloc(void){
    if(FREE_HEAD!=NULL){
        MainChain* temp=FREE_HEAD;
        while(temp!=NULL){
            delete_MainNode(&temp);
        }
    }
    // if(MEMORY_HEAD!=NULL){
    //     ProcessChain* temp=MEMORY_HEAD;
    //     while(temp!=NULL){
    //         delete_Process(&temp);
    //     }
    // }
} 

void free_list_info(void){
    printf("FreeList:\n");
    MainChain* temp=FREE_HEAD;
    SideChain* temp2=NULL;
    int s1=0,s2=0,free=0;
    int i=1,x=1;
    do{
        if(temp!=NULL){
            s2=(temp->pages)*PAGE_SIZE-1;
            printf("MainChain Node - %d Mem_size[ %d : %d ] -> ", i, s1, s2);
            temp2=temp->side_chain;
            x=1;
            do{
                if(temp2!=NULL){
                    s2=s1+temp2->size-1;
                    if(temp2->status==HOLE){
                        printf("SideChain Node - %d Mem_size[ %d : %d ] ( HOLE ) <-> ", x, s1, s2);
                        free+=temp2->size;
                    }
                    else
                        printf("SideChain Node - %d Mem_size[ %d : %d ] ( PROCESS ) <-> ", x, s1, s2);
                    s1=s2+1;
                    temp2=temp2->next;
                    x++;
                }
            }while(temp2!=temp->side_chain);
            temp=temp->next;
            i++;
        }
        printf("NULL\n");
    }while(temp!=FREE_HEAD);
    printf("Pages used => %d\n",(int)s1/PAGE_SIZE);
    printf("Free Memory => %d\n", free);
}

void * my_mem_to_physical_addr(void *v_ptr){
    return NULL;
}