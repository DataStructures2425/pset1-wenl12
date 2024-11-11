//segmentation fault basically everywhere 
#include "list.h"
#include "helpers.h"
#include <iostream>
#include <cstring>
using namespace std;

#define MAXORDER 21
#define MINORDER 12
#define PAGESIZE (1UL << 12)
#define NPAGES   512 // MEMSIZE_PHYSICAL / PAGESIZE

//kalloc not done :((
//kfree is probably fine ?

// Next free physical address for kalloc
uintptr_t next_free_pa = 0;

uintptr_t getBuddy(uintptr_t pa, int o);
void init_kalloc();
void* kalloc(size_t sz);
void kfree(void* ptr);

struct page {
    list_links link;
    int order;
    uintptr_t address;
    bool free = 1;
};

list <page, &page :: link> orders[22]; //free list
page pageArray[NPAGES + 1];

uintptr_t getBuddy(uintptr_t pa, int o)
{
    return pa ^ (1 << o);
}

//freelist[o].front() first thing

// init_kalloc
//    Initialize stuff needed by `kalloc`. Should be called
//    in testpset1.cpp before using 'kalloc' and 'bfree'. 
void init_kalloc() {
    pageArray[0].order = 21;
    for (int index = 0; index <= 512; index++){
        pageArray[index].address = index * 4096;
    }
    pageArray[0].free = 1;
    orders[21].push_back(&pageArray[0]);
    cout << "init alloc done!! awesome" << endl;
}

// kalloc(sz)
//    Allocate and return a pointer to at least `sz` contiguous bytes of
//    memory. Returns `nullptr` if `sz == 0` or on failure.
//
//    The caller should initialize the returned memory before using it.
//    The handout allocator sets returned memory to 0xCC 

void* kalloc(size_t sz) 
{
    //special case 
    if (sz == 0) return nullptr;

    void* ptr = nullptr;
    cout << "ALLOCATING" << endl;

    int order = msb(sz - 1);
    if (order < 12){
        order = 12; 
    }
    int currentOrder = order;

    while (currentOrder <= 21){
        //empty means FULL!!
        //special case for 21
        if (currentOrder == 21 && !orders[21].empty()){
            cout << "SPECIAL CASE 21" << endl;
            page* page = orders[currentOrder].pop_front();
            int index = page->address / 4096;
            pageArray[index].free = 0;
            return page;
        }

        //searching for nearest unoccupied order
        while (orders[currentOrder].empty()){
            currentOrder++;
            if (currentOrder > 21){
                cout << "no free blocks" << endl;
                return ptr;
            }
        }
        while (currentOrder >= order){
            //allocating data
            if (currentOrder == order){
                page* p = orders[currentOrder].pop_front();
                int indexOfP = p->address / 4096;
                pageArray[indexOfP].free = 0;
                ptr = p;
                break;
            } else { //break blocks if currentOrder > order 
                page* pa = orders[currentOrder].pop_front();
                currentOrder--;
                int indexOfPa = pa->address / 4096;
                int buddyIndex = getBuddy(indexOfPa * 4096, currentOrder);
                orders[currentOrder].push_back(&pageArray[buddyIndex]);
                orders[currentOrder].push_back(&pageArray[indexOfPa]);
            }
        }
    }

    cout << "ALLOCATED";
    return ptr;
}

// kfree(ptr)
//    Free a pointer previously returned by `kalloc`. Does nothing if
//    `ptr == nullptr`.
//doesnt work THERES A SEGMENTATION FAULT??????
void kfree(void* ptr) {
    // YOUR CODE HERE
    //cout << "kfree not implemented yet!" << endl;
    cout << "FREEING" << endl;
    int index = kptr2pa(ptr) / 4096;
    int order = pageArray[index].order;
    int buddyIndex = getBuddy(index, order) / 4096;
    if (order == 21){
        orders[order].push_back(&pageArray[index]);
        pageArray[index].free = 1;
    }
    if (ptr != nullptr){
        //if both the page and its buddy are free
        while (pageArray[index].free == 1 && pageArray[buddyIndex].free == 1){
            //get rid of them from the free list
            orders[order].erase(&pageArray[index]);
            orders[order].erase(&pageArray[buddyIndex]);
            order++;
            //add 1 block with one order higher
            orders[order].push_back(&pageArray[index]);
            pageArray[index].free = 1;
        }
    }
    cout << "FREED" << endl;
}