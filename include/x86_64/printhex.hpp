#pragma once

#include <stl/cstdlib/cstdint.h>
#include <x86_64/drivers/serial_legacy.hpp>

namespace firefly::kernel {
    //prints ram dump to serial port
    void print_ramdata(char *p, uint64_t size);
}