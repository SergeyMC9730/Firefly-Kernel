#pragma once

#include <stl/cstdlib/cstdint.h>
#include <x86_64/drivers/ports.hpp>
#include <x86_64/registers.hpp>
#include <x86_64/int/interrupt.hpp>
#include <x86_64/drivers/serial_legacy.hpp>
#include <stl/cstdlib/stdio.h>
#include <x86_64/interrupts.hpp>

namespace firefly::drivers::pit {
        #define PIT_COUNTER0 0
        #define PIT_COUNTER1 64
        #define PIT_COUNTER2 128
        #define PIT_COUNTER0P 0x40
        #define PIT_COUNTER1P 0x41
        #define PIT_COUNTER2P 0x42
        #define PIT_MODE_INT_ON_TERM 0
        #define PIT_MODE_HARDWARE_RETRIGGER 2
        #define PIT_MODE_RATE_GENERATOR 4
        #define PIT_MODE_SQUARE_WAVE 6
        #define PIT_MODE_SOFTWARE_STROBE 8
        #define PIT_MODE_HARDWARE_STROBE 10
    
    constexpr int pit_defs[] = {
        0x40,    //port a          0
        0x41,    //port b          1
        0x42,    //port c          2
        0x43,    //control port    3
        0xFC,    //mask            4
        1193180, //scale           5
        0x36     //set             6
    };
    
    constexpr int timer_irq = 0;

    extern uint64_t ticks;
    extern uint8_t subticks;

    void timer_phase(int hz, uint8_t counter, uint8_t mode, uint8_t port);
    void handler(iframe *i);
    void init();
}