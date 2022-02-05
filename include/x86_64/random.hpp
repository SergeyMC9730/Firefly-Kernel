#pragma once

#include <stl/cstdlib/cstdint.h>

namespace firefly::kernel::randomizer {
    int rand();
    void srand(unsigned int seed);
    
    uint64_t rdseed(uint64_t a);
    uint32_t rdseed(uint32_t b);
    uint16_t rdseed(uint16_t c);
}