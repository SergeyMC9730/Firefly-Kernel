#pragma once

#include <x86_64/memory-manager/greenleafy.hpp>

namespace firefly::kernel::mp {
    struct Process {
        unsigned char used;
        unsigned char onetime;
        void (*func)(Process *process);
        firefly::mm::greenleafy::memory_block *block;
        char *nid;
        uint64_t called_times;
    };
    extern bool has_updated;
    extern Process processes[0xFF];

    uint8_t make(void (*func)(Process *process), unsigned char run_one_time, char *nid);
    uint8_t make(void (*func)(Process *process), unsigned char run_one_time);
    void run();
    void close(uint8_t id);
    void turn_off();
    void turn_on();
    void clear();
}