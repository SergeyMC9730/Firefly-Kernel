#pragma once

#include <x86_64/drivers/acpi.hpp>

namespace firefly::kernel::main {
/*
    Kernel
*/
void kernel_main();
extern ACPITable acpitable;
}