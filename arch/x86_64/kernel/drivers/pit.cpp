#include <x86_64/drivers/pit.hpp>

using namespace firefly::kernel::io;
using namespace firefly::kernel::registers;

namespace firefly::drivers::pit {
    uint64_t ticks;
    uint8_t subticks;

    void timer_phase([[maybe_unused]] int hz, [[maybe_unused]] uint8_t counter, [[maybe_unused]] uint8_t mode){
        cli();
        // int divisor = pit_defs[5] / hz;
        // outb(pit_defs[3], 0 | mode | 48 | counter);
        // outb(counter, divisor & 0xFc);
        // outb(counter, (divisor >> 8) & 0xFc);
        // uint32_t div = 1193180 / hz;
        // outb(0x43, 0x36);

        // uint8_t l = (uint8_t)(div & 0xFF);
        // uint8_t h = (uint8_t)((div >> 8) & 0xFF);

        // outb(0x43, l);
        // outb(0x43, h);
        outb(0x43, 0x34);
        outb(0x40, 0xa9);
        outb(0x40, 0x04);
        sti();
    }
    
    void handler([[maybe_unused]] iframe *i){
        if(++subticks == 100){
            ticks++;
            subticks = 0;
        }
        
        firefly::kernel::io::legacy::writeTextSerial("%d | timer fires!!!\n", ticks);
        printf("%d | timer fires!!!\n", ticks);
        firefly::kernel::core::interrupt::ack(timer_irq);
    }
    void init(){
        cli();
        timer_phase(1000, PIT_COUNTER0, PIT_MODE_SQUARE_WAVE);
        //firefly::kernel::core::interrupt::change::update(&handler, 8, 0x8E, 0);
        //firefly::kernel::core::interrupt::change::update(&handler, 8, 0x8E, 2);
        sti();
    }
}