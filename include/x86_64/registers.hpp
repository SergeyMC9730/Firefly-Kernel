#pragma once

#include <stl/cstdlib/cstdint.h>

namespace firefly::kernel::registers {
    typedef struct regs {
        uint32_t gs, fs, es, ds;
        uint32_t edi, esi, ebp, esp, ebx, ecx, eax;
    } regs_t;
    regs_t get();
    void set(regs_t *r);
}