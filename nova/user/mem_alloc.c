#include "mem_alloc.h"
#include <stdio.h>
#include <stddef.h>

/*
 * Template for 11malloc. If you want to implement it in C++, rename
 * this file to mem_alloc.cc.
 */

static inline void *nbrk(void *address);

#ifdef NOVA

/**********************************/
/* nbrk() implementation for NOVA */
/**********************************/

static inline unsigned syscall2(unsigned w0, unsigned w1)
{
    asm volatile("   mov %%esp, %%ecx    ;"
                 "   mov $1f, %%edx      ;"
                 "   sysenter            ;"
                 "1:                     ;"
                 : "+a"(w0)
                 : "S"(w1)
                 : "ecx", "edx", "memory");
    return w0;
}

static void *nbrk(void *address)
{
    return (void *)syscall2(3, (unsigned)address);
}
#else

/***********************************/
/* nbrk() implementation for Linux */
/***********************************/

#include <unistd.h>

static void *nbrk(void *address)
{
    void *current_brk = sbrk(0);
    if (address != NULL) {
        int ret = brk(address);
        if (ret == -1)
            return NULL;
    }
    return current_brk;
}

#endif

// structure that represents information about a memory block
typedef struct block_inf_t {
    unsigned int size;
    unsigned int is_free;                // 0 - allocated, 1 - free
    struct block_inf_t* next;
    struct block_inf_t* prev;
} block_inf_t;

block_inf_t* head = NULL;                 // linked list(of memory blocks) head
block_inf_t* tail = NULL;                 // linked list(of memory blocks) tail

void* min_break = NULL;                   // min possible brk

// function to find a fitted memory block (splits the block if it is too big)
block_inf_t* find_fitted_block_inf(unsigned long size) {
    if (size == 0) return NULL;

    block_inf_t* cur = head;
    while (cur != NULL) {
        if (cur->is_free == 1 && cur->size >= size) {       
            if (cur->size > sizeof(block_inf_t) + size) {         // split block if it is too big
                block_inf_t* new_block_inf = (block_inf_t*)((char*)cur + size + sizeof(block_inf_t));
                new_block_inf->size = cur->size - size - sizeof(block_inf_t);
                new_block_inf->is_free = 1;
                new_block_inf->next = cur->next;
                new_block_inf->prev = cur;
                cur->next = new_block_inf;
                cur->size = size;
                
                if (new_block_inf->next == NULL) {                // update tail if necessary
                    tail = new_block_inf;           
                } else {
                    new_block_inf->next->prev = new_block_inf;
                }     
            }

            cur->is_free = 0;
            return cur;
        }

        cur = cur->next;
    }

    return NULL;
}

// function to merge adjacent free blocks (always called after my_free)
void connect_free_blocks(block_inf_t* free_block_inf) {
    if (free_block_inf == NULL || free_block_inf->is_free == 0) return;

    if (free_block_inf->next != NULL && free_block_inf->next->is_free == 1) {  // merge current block with next
        block_inf_t* next = free_block_inf->next;
        free_block_inf->size += next->size + sizeof(block_inf_t);
        free_block_inf->next = next->next;
    }

    if (free_block_inf->prev != NULL && free_block_inf->prev->is_free == 1) {  // merge current block with previous
        block_inf_t* prev = free_block_inf->prev;
        prev->size += free_block_inf->size + sizeof(block_inf_t);
        prev->next = free_block_inf->next;
        free_block_inf = prev;
    }

    if (free_block_inf->next == NULL){                                         // update tail if necessary                                
        tail = free_block_inf;
    } else {
        free_block_inf->next->prev = free_block_inf;
    }    
}

// allocate memory of the given size
void *my_malloc(unsigned long size) {
    if (size == 0) return NULL;

    if (min_break == NULL) {                       // initialize min_break on first call
        min_break = nbrk(0);
    }

    block_inf_t* fitted_block_inf = find_fitted_block_inf(size);   // attempt to find a fitted block
    if (fitted_block_inf != NULL) {
        return (void*)(fitted_block_inf + 1);
    }

    void* new_brk = nbrk((void*)((char*)nbrk(0) + sizeof(block_inf_t) + size));   // attempt to increase brk
    if (new_brk == 0) {
        return NULL;
    }

    block_inf_t* new_block = (block_inf_t*)new_brk;
    new_block->size = size;
    new_block->is_free = 0;
    new_block->next = NULL;
    new_block->prev = tail;

    if (head == NULL) {                            // initialize linked list if empty
        head = new_block;
        tail = new_block;
    } else {
        tail->next = new_block;
        tail = new_block;
    }

    return (void*)(new_block + 1);
}

// free the allocated memory block
int my_free(void *address) {
    if (address == NULL || address < min_break || address > nbrk(0)) return -1;

    block_inf_t* block_inf = (block_inf_t*)address - 1;

    if (block_inf->is_free == 1) return -1;          // block is already free

    block_inf->is_free = 1;
    connect_free_blocks(block_inf);                  // merge adjacent free blocks
    return 0;
}