#include <x86_64/memory-manager/malloc.hpp>

namespace firefly::mm::smalloc {
    char alloc_table[alloc_table_size];
    int offset;

    //static memory allocator
    MemoryStruct smalloc(int size){
	    MemoryStruct mem_s;
	    mem_s.offset = offset;
	    mem_s.size = size;
	    mem_s.address = &alloc_table[offset];
	    offset += size;
	    return mem_s;
    }
}