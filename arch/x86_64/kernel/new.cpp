#include <stl/cstdlib/cstdint.h>
#include <x86_64/memory-manager/malloc.hpp>
#include <x86_64/new.hpp>

void *operator new(size_t size)
{
    return firefly::mm::smalloc::smalloc(size).address;
}

void *operator new[](size_t size)
{
    return firefly::mm::smalloc::smalloc(size).address;
}
//later
void operator delete([[maybe_unused]] void *p)
{
    return;
}
//later
void operator delete[]([[maybe_unused]] void *p)
{
    return;
}