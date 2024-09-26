#include "list.h"
#include "helpers.h"
#include <iostream>
#include <cstring>
using namespace std;

#define MAXORDER 21
#define MINORDER 12
#define PAGESIZE (1UL << 12)
#define NPAGES   512 // MEMSIZE_PHYSICAL / PAGESIZE


// Next free physical address for kalloc
uintptr_t next_free_pa = 0;

uintptr_t getBuddy(uintptr_t pa, int o);
void init_kalloc();
void* kalloc(size_t sz);
void kfree(void* ptr);

struct page {
    // YOUR CODE HERE
};


uintptr_t getBuddy(uintptr_t pa, int o)
{
    // YOUR CODE HERE
}

// init_kalloc
//    Initialize stuff needed by `kalloc`. Should be called
//    in testpset1.cpp before using 'kalloc' and 'bfree'. 
void init_kalloc() {
    // YOUR CODE HERE
}


// kalloc(sz)
//    Allocate and return a pointer to at least `sz` contiguous bytes of
//    memory. Returns `nullptr` if `sz == 0` or on failure.
//
//    The caller should initialize the returned memory before using it.
//    The handout allocator sets returned memory to 0xCC 
void* kalloc(size_t sz) 
{
    // REWRITE 
    if (sz > PAGESIZE) return nullptr;

    void* ptr = nullptr;

    if (next_free_pa < (1UL << 21))
    {
        ptr = pa2kptr(next_free_pa);
        next_free_pa += PAGESIZE;
    }

    if (ptr) memset(ptr, 0xCC, PAGESIZE);

    return ptr;
}


// kfree(ptr)
//    Free a pointer previously returned by `kalloc`. Does nothing if
//    `ptr == nullptr`.
void kfree(void* ptr) {
    // YOUR CODE HERE
    cout << "kfree not implemented yet!" << endl;
}