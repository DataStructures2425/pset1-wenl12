#include <cstdlib>

void* alloc_region = malloc(1UL << 21);

uintptr_t start_addr = reinterpret_cast<uintptr_t>(alloc_region);


// Converts a physical address into a ptr
void* pa2kptr(uintptr_t pa)
{
    return reinterpret_cast<void*>(pa+start_addr);
}

// Converts ptr returned from kalloc into a physical address
uintptr_t kptr2pa(void* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr) - start_addr;
}

// Returns most significant bit for binary number x,
// use msb(sz-1) to find appropriate order for an allocation
inline constexpr int msb(unsigned x) {
    return x ? sizeof(x) * 8 - __builtin_clz(x) : 0;
}
