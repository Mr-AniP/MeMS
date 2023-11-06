#include "mainimpl.h"
// page calculation function
int pagesRequired(int s){
    s+=sizeof(MainChain)+sizeof(SideChain)+sizeof(ProcessChain);
    float f=(float)s/PAGE_SIZE;
    s=(int)f;
    if(f==s){
        return s;
    }
    else{
        return s+1;
    }
}

// implementation of mems.h functions
MainChain* FREE_HEAD ;
ProcessChain* MEMORY_HEAD;
void my_mem_init(void){
    FREE_HEAD=NULL;
    MEMORY_HEAD=NULL;
}

void *my_mem_alloc(size_t size){
    MainChain* temp=FREE_HEAD;
    SideChain* temp2=NULL;
    int vmin=0;
    int vmax=0;
    int s3=0;
    do{
        if(temp!=NULL){
            temp2=temp->side_chain;
            vmin+=vmin+sizeof(MainChain);
            do{
                if(temp2!=NULL){
                    vmin+=sizeof(SideChain);
                    if(temp2->status==HOLE && temp2->size>=(size+sizeof(ProcessChain))){
                        vmin+=sizeof(ProcessChain);
                        if(temp2->size > size + sizeof(SideChain) + sizeof(ProcessChain)){
                            insert_SideNode(temp2,size,sizeof(ProcessChain));
                        }
                        temp2->status=PROCESS;
                        vmax=vmin+size-1;
                        insert_Process(&MEMORY_HEAD,(void*)((char*)temp2 + sizeof(SideChain)),(void*)((char*)temp2 + sizeof(SideChain)+sizeof(ProcessChain)),(uintptr_t) vmax, (uintptr_t) vmin);
                        return (void*)(uintptr_t) vmin;
                    }
                    else if(temp2->status==PROCESS){
                        vmin+=sizeof(ProcessChain)+temp2->size;
                    }
                    temp2=temp2->next;
                }
            }while(temp2!=temp->side_chain);
            temp=temp->next;
        }
    }while(temp!=FREE_HEAD);

    insert_MainNode(&FREE_HEAD,pagesRequired(size));
    vmin+=sizeof(SideChain)+sizeof(MainChain);
    vmax=vmin+size-1;
    temp2=FREE_HEAD->prev->side_chain;
    if(temp2->size > size + sizeof(SideChain)+ sizeof(ProcessChain)){
        insert_SideNode(temp2,size,sizeof(ProcessChain));
    }
    temp2->status=PROCESS;
    insert_Process(&MEMORY_HEAD,(void*)((char*)temp2 + sizeof(SideChain)),(void*)((char*)temp2 + sizeof(SideChain)+sizeof(ProcessChain)),(uintptr_t) vmax, (uintptr_t) vmin);
    return (void*)(uintptr_t) vmin;
}


void mem_dealloc(void){
    if(MEMORY_HEAD!=NULL){
        while(MEMORY_HEAD!=NULL){
            delete_Process(&MEMORY_HEAD,MEMORY_HEAD);
        }
    }
    if(FREE_HEAD!=NULL){
        MainChain* temp=FREE_HEAD;
        while(temp!=NULL){
            delete_MainNode(&temp); 
        }
    }
    //this will atomatically delete complete memory chain and free all the memory
} 

void free_list_info(void){
    printf("\nFreeList:\n\n");
    MainChain* temp=FREE_HEAD;
    SideChain* temp2=NULL;
    int s1=0,s2=0,free=0,s3=0;
    int i=1;
    do{
        if(temp!=NULL){
            s3=s1+(temp->pages*PAGE_SIZE)-1;
            printf("MainNode-%d [%d : %d] -> ", i, s1, s3);
            s2=s1+sizeof(MainChain)-1;
            printf("M_NODE[%d : %d] <-> ", s1, s2);
            s1=s2+1;
            temp2=temp->side_chain;
            do{
                if(temp2!=NULL){
                    s2=s1+sizeof(SideChain)-1;
                    printf("S_NODE[%d : %d] <-> ", s1, s2);
                    s1=s2+1;
                    if(temp2->status==HOLE){
                        s2=s1+temp2->size-1;
                        printf("HOLE[%d : %d] <-> ",s1, s2);
                        free+=temp2->size;
                    }
                    else{
                        s2=s1+sizeof(ProcessChain)-1;
                        printf("MMap_P[%d : %d] <-> ", s1, s2);
                        s1=s2+1;
                        s2=s1+temp2->size-1;
                        printf("PROCESS[%d : %d] <-> ",s1, s2);
                        }
                    s1=s2+1;
                    temp2=temp2->next;
                }
            }while(temp2!=temp->side_chain);
            s1=s3+1;
            temp=temp->next;
            i++;
        }
        printf("NULL\n");
    }while(temp!=FREE_HEAD);
    printf("Pages used => %d\n",(int)s1/PAGE_SIZE);
    printf("Free Memory => %d\n", free);
}

void * my_mem_to_physical_addr(void *v_ptr){
    uintptr_t  v_ptr1=(uintptr_t)v_ptr;
    ProcessChain* temp=MEMORY_HEAD;
    while(temp!=NULL){
        if(temp->virt_max>=v_ptr1 && temp->virt_min<=v_ptr1){
            return temp->phys_addr + (v_ptr1-temp->virt_min);
        }
        temp=temp->next;
    }
    return NULL;
}

void my_mem_free(void *ptr){
    ptr=my_mem_to_physical_addr(ptr);
    ptr=((char*)ptr -sizeof(ProcessChain));
    SideChain* node= (SideChain*)((char*)ptr -sizeof(SideChain));
    delete_Process(&MEMORY_HEAD,(ProcessChain*)ptr);
    node->status=HOLE;
    node->size+=sizeof(ProcessChain);
    while(try_merge(&node)!=0);
}