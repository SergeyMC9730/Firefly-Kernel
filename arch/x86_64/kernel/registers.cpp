#include <x86_64/registers.hpp>

namespace firefly::kernel::registers {
    regs_t get() {
        regs_t regs;
        //16 bit registers
        asm ("movw %%ax, %0"
        : "=a" (regs.u16.ax)
        );
        asm ("movw %%bx, %0"
        : "=b" (regs.u16.bx)
        );
        asm ("movw %%cx, %0"
        : "=c" (regs.u16.cx)
        );
        asm ("movw %%dx, %0"
        : "=d" (regs.u16.dx)
        );
        asm ("movw %%si, %0"
        : "=S" (regs.u16.si)
        );
        asm ("movw %%di, %0"
        : "=D" (regs.u16.di)
        );
        //32 bit registers
        asm ("movl %%eax, %0"
        : "=a" (regs.u32.eax)
        );
        asm ("movl %%ebx, %0"
        : "=b" (regs.u32.ebx)
        );
        asm ("movl %%ecx, %0"
        : "=c" (regs.u32.ecx)
        );
        asm ("movl %%edx, %0"
        : "=d" (regs.u32.edx)
        );
        asm ("movl %%esi, %0"
        : "=S" (regs.u32.esi)
        );
        asm ("movl %%edi, %0"
        : "=D" (regs.u32.edi)
        );
        //64 bit registers
        asm ("movq %%rax, %0"
        : "=a" (regs.u64.rax)
        );
        asm ("movq %%rbx, %0"
        : "=b" (regs.u64.rbx)
        );
        asm ("movq %%rcx, %0"
        : "=c" (regs.u64.rcx)
        );
        asm ("movq %%rdx, %0"
        : "=d" (regs.u64.rdx)
        );
        asm ("movq %%rsi, %0"
        : "=S" (regs.u64.rsi)
        );
        asm ("movq %%rdi, %0"
        : "=D" (regs.u64.rdi)
        );
        return regs;
    }
    void set(regs_t r) {
        //16 bit registers
        asm ("movw %0, %%ax"
        :
        : "a" (r.u16.ax)
        );
        asm ("movw %0, %%bx"
        :
        : "b" (r.u16.bx)
        );
        asm ("movw %0, %%cx"
        :
        : "c" (r.u16.cx)
        );
        asm ("movw %0, %%dx"
        :
        : "d" (r.u16.dx)
        );
        asm ("movw %0, %%si"
        :
        : "S" (r.u16.si)
        );
        asm ("movw %0, %%di"
        :
        : "D" (r.u16.di)
        );
        //32 bit registers
        asm ("movl %0, %%eax"
        :
        : "a" (r.u32.eax)
        );
        asm ("movl %0, %%ebx"
        :
        : "b" (r.u32.ebx)
        );
        asm ("movl %0, %%ecx"
        :
        : "c" (r.u32.ecx)
        );
        asm ("movl %0, %%edx"
        :
        : "d" (r.u32.edx)
        );
        asm ("movl %0, %%esi"
        :
        : "S" (r.u32.esi)
        );
        asm ("movl %0, %%edi"
        :
        : "D" (r.u32.edi)
        );
        //64 bit registers
        asm ("movq %0, %%rax"
        :
        : "a" (r.u64.rax)
        );
        asm ("movq %0, %%rbx"
        :
        : "b" (r.u64.rbx)
        );
        asm ("movq %0, %%rcx"
        :
        : "c" (r.u64.rcx)
        );
        asm ("movq %0, %%rdx"
        :
        : "d" (r.u64.rdx)
        );
        asm ("movq %0, %%rsi"
        :
        : "S" (r.u64.rsi)
        );
        asm ("movq %0, %%rdi"
        :
        : "D" (r.u64.rdi)
        );
    }
}