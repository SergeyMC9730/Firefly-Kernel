#pragma once

namespace firefly::mm::smalloc {
    constexpr int alloc_table_size = 8192 * 1024;
    extern char alloc_table[alloc_table_size];
    extern int offset;
    struct MemoryStruct {
	    int offset;
	    int size;
	    void *address;
    };
    MemoryStruct smalloc(int size);
}