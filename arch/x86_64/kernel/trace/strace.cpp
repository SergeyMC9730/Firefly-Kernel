#include <stl/cstdlib/stdio.h>
#include <x86_64/libk++/iostream.h>
#include <stl/array.h>

#include <x86_64/trace/symbols.hpp>

#include <x86_64/interrupts.hpp>

namespace firefly::trace {

void trace_stack();

/*
    Kernel panic
*/
[[noreturn]] void panic(const char *P_REASON, const int P_ERRCODE) {
    printf("**** KERNEL PANIC ****\nReason    : %s\nError Code: 0x%08X\n\n", P_REASON, P_ERRCODE);
    trace_stack();

    cli();

    while (1)
        ;
}

/*
    Stack frame
*/
struct stackframe {
    struct stackframe *frame;
    uint64_t rip;
};

/*
    Prints contents of stack
*/
void trace_stack() {
    printf("Stack trace:\n");
    struct stackframe *stkf;
    asm("mov %%rbp, %0"
        : "=r"(stkf));
    for (int i = 0; i < 10 && stkf; i++) {
        if (!backtrace(stkf->rip, i))
            break;
        stkf = stkf->frame;
    }
}
}  // namespace firefly::trace
