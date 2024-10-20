#include "alloc.h"
#include <iostream>
using namespace std;

int main()
{

    init_kalloc();

    void* ptr1 = kalloc(0);
    void* ptr2 = kalloc(1 << 21);
    void* ptr3 = kalloc(1 << 14);
    kfree(ptr2);
    void* ptr4 = kalloc(1 << 14);
    void* ptr5 = kalloc(1 << 14);

    kfree(ptr3);
    kfree(ptr5);
    kfree(ptr4);

    void* ptr6 = kalloc(1 << 21);
    kfree(ptr6);
    
    void* ptr7 = kalloc(1 << 21);
    kfree(ptr7);

    void* ptr8 = kalloc(1 << 20);
    void* ptr9 = kalloc(1 << 19);

}