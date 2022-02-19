#pragma once

typedef struct __attribute__((packed)) {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
    uint64_t err;
    uint64_t int_no;
} iframe_t;

typedef struct __attribute__((packed)) {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t ist;
    uint8_t attributes;
    uint16_t isr_mid;
    uint32_t isr_high;
    uint32_t reserved;
} idt_t;

typedef struct  __attribute__((packed)) {
    uint16_t limit;
    uint64_t base;
} idtr_t;

namespace firefly::kernel::core::interrupt {
    extern __attribute__((aligned(0x10))) idt_t idt[256];
    extern idtr_t idtr;
    extern "C" void *isr_stub_table[32];
    extern "C" void popa64();
    extern "C" void pusha64();
    
    void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags);
    void init();

    __attribute__((interrupt)) void interrupt_handler([[maybe_unused]] iframe_t *frame);
    // void init();

    // // test interrupt handler
    // void test_int();

    // extern bool is_crashed;

    // namespace change{ 
    //     void update(void (*handler)(iframe *), uint16_t cs, uint8_t type, uint8_t index);
    // }
    
    // void ack(int n);

}  // namespace firefly::kernel::interrupt

__attribute__((interrupt)) extern "C" void exception_handler([[maybe_unused]] iframe_t *frame);