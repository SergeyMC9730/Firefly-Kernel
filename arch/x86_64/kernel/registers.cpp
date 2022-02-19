#include <x86_64/registers.hpp>
#include <x86_64/int/interrupt.hpp>

namespace firefly::kernel::registers {
    regs_t get() {
        regs_t regs;
        firefly::kernel::core::interrupt::pusha64();
        //16 bit registers
        asm volatile ("movw %%ax, %0"
        : "=a" (regs.u16.ax)
        );
        asm volatile ("movw %%bx, %0"
        : "=b" (regs.u16.bx)
        );
        asm volatile ("movw %%cx, %0"
        : "=c" (regs.u16.cx)
        );
        asm volatile ("movw %%dx, %0"
        : "=d" (regs.u16.dx)
        );
        asm volatile ("movw %%si, %0"
        : "=S" (regs.u16.si)
        );
        asm volatile ("movw %%di, %0"
        : "=D" (regs.u16.di)
        );
        //32 bit registers
        asm volatile ("movl %%eax, %0"
        : "=a" (regs.u32.eax)
        );
        asm volatile ("movl %%ebx, %0"
        : "=b" (regs.u32.ebx)
        );
        asm volatile ("movl %%ecx, %0"
        : "=c" (regs.u32.ecx)
        );
        asm volatile ("movl %%edx, %0"
        : "=d" (regs.u32.edx)
        );
        asm volatile ("movl %%esi, %0"
        : "=S" (regs.u32.esi)
        );
        asm volatile ("movl %%edi, %0"
        : "=D" (regs.u32.edi)
        );
        //64 bit registers
        asm volatile ("movq %%rax, %0"
        : "=a" (regs.u64.rax)
        );
        asm volatile ("movq %%rbx, %0"
        : "=b" (regs.u64.rbx)
        );
        asm volatile ("movq %%rcx, %0"
        : "=c" (regs.u64.rcx)
        );
        asm volatile ("movq %%rdx, %0"
        : "=d" (regs.u64.rdx)
        );
        asm volatile ("movq %%rsi, %0"
        : "=S" (regs.u64.rsi)
        );
        asm volatile ("movq %%rdi, %0"
        : "=D" (regs.u64.rdi)
        );
        firefly::kernel::core::interrupt::popa64();
        return regs;
    }
    void set(regs_t r) {
        //16 bit registers
        asm volatile ("movw %0, %%ax"
        :
        : "a" (r.u16.ax)
        );
        asm volatile ("movw %0, %%bx"
        :
        : "b" (r.u16.bx)
        );
        asm volatile ("movw %0, %%cx"
        :
        : "c" (r.u16.cx)
        );
        asm volatile ("movw %0, %%dx"
        :
        : "d" (r.u16.dx)
        );
        asm volatile ("movw %0, %%si"
        :
        : "S" (r.u16.si)
        );
        asm volatile ("movw %0, %%di"
        :
        : "D" (r.u16.di)
        );
        //32 bit registers
        asm volatile ("movl %0, %%eax"
        :
        : "a" (r.u32.eax)
        );
        asm volatile ("movl %0, %%ebx"
        :
        : "b" (r.u32.ebx)
        );
        asm volatile ("movl %0, %%ecx"
        :
        : "c" (r.u32.ecx)
        );
        asm volatile ("movl %0, %%edx"
        :
        : "d" (r.u32.edx)
        );
        asm volatile ("movl %0, %%esi"
        :
        : "S" (r.u32.esi)
        );
        asm volatile ("movl %0, %%edi"
        :
        : "D" (r.u32.edi)
        );
        //64 bit registers
        asm volatile ("movq %0, %%rax"
        :
        : "a" (r.u64.rax)
        );
        asm volatile ("movq %0, %%rbx"
        :
        : "b" (r.u64.rbx)
        );
        asm volatile ("movq %0, %%rcx"
        :
        : "c" (r.u64.rcx)
        );
        asm volatile ("movq %0, %%rdx"
        :
        : "d" (r.u64.rdx)
        );
        asm volatile ("movq %0, %%rsi"
        :
        : "S" (r.u64.rsi)
        );
        asm volatile ("movq %0, %%rdi"
        :
        : "D" (r.u64.rdi)
        );
    }
}