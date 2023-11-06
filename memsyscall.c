#include "memsyscall.h"
// Function to use system call to allocate memory pages
#define FLAGS (MAP_ANONYMOUS | MAP_PRIVATE)
void *page_allocater(int pages)
{
    size_t size = PAGE_SIZE * pages; // Size of the memory region in bytes 

    // Allocate anonymous memory using mmap
    void *mem = (void *)mmap(NULL, size, PROT_READ | PROT_WRITE, FLAGS, -1, 0);
    printf("Memory mapped using mmap.\n");
    if (mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    return mem;
}

// Function to use system call to free memory pages
void page_free(void *addr, int pages)
{
    size_t size = PAGE_SIZE * pages;
    if (munmap(addr, size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    printf("Memory released using munmap.\n");
}
