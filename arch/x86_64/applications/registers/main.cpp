#include <stl/cstdlib/stdio.h>
#include <stl/cstdlib/cstdint.h>
#include <x86_64/applications/registers/main.hpp>
#include <x86_64/registers.hpp>
#include <stl/cstdlib/stdio.h>

namespace firefly::applications::registers {
    int registers_main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
        firefly::kernel::registers::regs_t regs = firefly::kernel::registers::get();
        printf("AX: %X BX: %X CX: %X DX: %X SI: %X, DI: %X\n", regs.u16.ax, regs.u16.bx, regs.u16.cx, regs.u16.dx, regs.u16.si, regs.u16.di);
        printf("EAX: %X EBX: %X ECX: %X EDX: %X ESI: %X, EDI: %X\n", regs.u32.eax, regs.u32.ebx, regs.u32.ecx, regs.u32.edx, regs.u32.esi, regs.u32.edi);
        printf("RAX: %X RBX: %X RCX: %X RDX: %X RSI: %X, RDI: %X\n", regs.u64.rax, regs.u64.rbx, regs.u64.rcx, regs.u64.rdx, regs.u64.rsi, regs.u64.rdi);
        return 0;
    }

    int getc(){ return 1864850; }
}