#pragma once

#include <stl/cstdlib/cstdint.h>

namespace firefly::kernel::registers {
    typedef struct {
        struct u0 {
            uint16_t ax, bx, cx, dx, si, di;

            //Register Ignore List (works only on writing)
            // Will be implemented in the future to prevent breaking CPU registers
            //0 - ax
            //1 - bx
            //2 - cx
            //3 - dx
            //4 - si
            //5 - di
            bool ignorelist[6];
        } u16;
        struct u1 {
            uint32_t eax, ebx, ecx, edx, esi, edi;
                
            //Register Ignore List (works only on writing)
            // Will be implemented in the future to prevent breaking CPU registers
            //0 - eax
            //1 - ebx
            //2 - ecx
            //3 - edx
            //4 - esi
            //5 - edi
            bool ignorelist[6];
        } u32;
        struct u2 {
           uint64_t rax, rbx, rcx, rdx, rsi, rdi;

            //Register Ignore List (works only on writing)
            // Will be implemented in the future to prevent breaking CPU registers
            //0 - rax
            //1 - rbx
            //2 - rcx
            //3 - rdx
            //4 - rsi
            //5 - rdi
           bool ignorelist[6];
        } u64;
    } regs_t;
    regs_t get();
    void set(regs_t r);
}