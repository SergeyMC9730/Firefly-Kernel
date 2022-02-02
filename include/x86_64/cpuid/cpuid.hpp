#pragma once
#include <cpuid.h>
#include <x86_64/drivers/serial_legacy.hpp>

namespace firefly::kernel::cpuid {
    int get_model();
    int check_apic();
}