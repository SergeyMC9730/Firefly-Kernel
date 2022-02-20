#include <x86_64/drivers/pit.hpp>

using namespace firefly::kernel::io;
using namespace firefly::kernel::registers;

namespace firefly::drivers::pit {
    uint64_t ticks;
    uint8_t subticks;

    void send_eoi(uint8_t irq) {
        if(irq >= 8) outb(PIC2_COMMAND, PIC1);
        outb(PIC1_COMMAND, PIC1);
    }
    void remap(int offset1, int offset2) {
        [[maybe_unused]] uint8_t a1 = inb(PIC1_DATA);
        [[maybe_unused]] uint8_t a2 = inb(PIC2_DATA);

        outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
        io_pause();
        outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
        io_pause();
        outb(PIC1_DATA, offset1);
        io_pause();
        outb(PIC2_DATA, offset2);
        io_pause();
        outb(PIC1_DATA, 4);
        io_pause();
        outb(PIC2_DATA, 2);
        io_pause();
    
        outb(PIC1_DATA, ICW4_8086);
        io_pause();
        outb(PIC2_DATA, ICW4_8086);
        io_pause();
    
        outb(PIC1_DATA, 0xFD);
        outb(PIC2_DATA, 0xFF);

        sti();
    }
    void disable() {
        outb(0xA1, 0xFF);
        outb(0x21, 0xFF);
    }
    void mask(uint8_t irq) {
        uint16_t port;
        uint8_t value;

        if(irq < 8){
            port = PIC1_DATA;
        } else {
            port = PIC2_DATA;
            irq -= 8;
        }
        value = inb(port) | (1 << irq);
        outb(port, value);
    }
    void clear_mask(uint8_t irq) {
        uint16_t port;
        uint8_t value;
    
        if(irq < 8) {
            port = PIC1_DATA;
        } else {
            port = PIC2_DATA;
            irq -= 8;
        }
        value = inb(port) & ~(1 << irq);
        outb(port, value);
    }

    uint16_t get_irq(int ocw3) {
        outb(PIC1_COMMAND, ocw3);
        outb(PIC2_COMMAND, ocw3);
        return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
    }
    uint16_t get_irr() {
        return get_irq(PIC_READ_IRR);        
    }
    uint16_t get_isr() {
        return get_irq(PIC_READ_ISR);
    }

    void pit_handler([[maybe_unused]] iframe_t *frame){
        printf("pit handler!!\n");
        ticks++;
        firefly::drivers::pit::send_eoi(frame->int_no);
    }

    void init(){
        remap(0x20, 0x28);
        cli();
        int d = 1193182 / 1000;
        outb(0x43, 0 | 6 | 0x30 | 0x40);
        outb(0x40, d);
        outb(0x40, d >> 8);
        sti();
        // firefly::kernel::core::interrupt::change::update(&handler, 0x08, 0x8E, 0);
        // firefly::kernel::core::interrupt::change::update(&handler, 0x08, 0x8E, 32);
        //timer_phase(1000, PIT_COUNTER0, PIT_MODE_SQUARE_WAVE, PIT_COUNTER0P);
        //sti();
        //firefly::kernel::core::interrupt::test_int();
    }
}