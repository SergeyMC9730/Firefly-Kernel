#include <x86_64/drivers/pit.hpp>

using namespace firefly::kernel::io;
using namespace firefly::kernel::registers;

namespace firefly::drivers::pit {
    uint64_t ticks;
    uint8_t subticks;

    void timer_phase([[maybe_unused]] int hz, [[maybe_unused]] uint8_t counter, [[maybe_unused]] uint8_t mode, uint8_t port){
        cli();
        uint16_t divisor = 1193182 / hz;
        outb(0x43, 0x00 | mode | 0x30 | counter);
        outb(port, divisor & 0xFE);
        outb(port, divisor >> 8);
    }
    
    __attribute__((interrupt)) void handler([[maybe_unused]] iframe *i){
        if(++subticks == 100){
            ticks++;
            subticks = 0;
        }
        
        firefly::kernel::io::legacy::writeTextSerial("%d | timer fires!!!\n", ticks);
        printf("%d | timer fires!!!\n", ticks);
        firefly::kernel::core::interrupt::ack(timer_irq);
    }
    void init(){
        firefly::kernel::core::interrupt::change::update(&handler, 0x08, 0x8E, 0);
        firefly::kernel::core::interrupt::change::update(&handler, 0x08, 0x8E, 32);
        timer_phase(1000, PIT_COUNTER0, PIT_MODE_SQUARE_WAVE, PIT_COUNTER0P);
        sti();
        //firefly::kernel::core::interrupt::test_int();
    }
}