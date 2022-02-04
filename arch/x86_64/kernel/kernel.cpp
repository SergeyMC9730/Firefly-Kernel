#include <stl/array.h>
#include <stl/cstdlib/stdio.h>
#include <x86_64/libk++/iostream.h>
#include <stl/cstdlib/cstddef.h>

#include <x86_64/drivers/ps2.hpp>
#include <x86_64/drivers/serial.hpp>
#include <x86_64/drivers/serial_legacy.hpp>

#include <x86_64/drivers/vbe.hpp>
#include <x86_64/kernel.hpp>
#include <x86_64/trace/strace.hpp>

#include <x86_64/applications/application_manager.hpp>

#include <x86_64/memory-manager/greenleafy.hpp>

#include <x86_64/settings.hpp>

#include <x86_64/brainfuck/bf.hpp>

#include <x86_64/new.hpp>

#include <x86_64/drivers/pit.hpp>
#include <x86_64/cpuid/cpuid.hpp>
#include <x86_64/drivers/acpi.hpp>

#include <x86_64/registers.hpp>

[[maybe_unused]] constexpr short MAJOR_VERSION = 0;
[[maybe_unused]] constexpr short MINOR_VERSION = 0;
constexpr const char *VERSION_STRING = "0.1-x86_64-fork";

namespace firefly::kernel::main {
/*
    Prints Firefly's Contributors
*/
void write_ff_info() {
    printf("Firefly\nVersion: %s\nContributors:", VERSION_STRING);

    firefly::std::array<const char *, 4> arr = {
        "Lime\t  ", "JohnkaS", "V01D-NULL\t  ", "SergeyMC9730"
    };

    for (size_t i = 0; i < arr.max_size(); i++) {
        if (i % (arr.max_size() - 1) == 0) {
            puts("\n\t");
        }
        printf("%s  ", arr[i]);
    }
    puts("\n");
}

/*
    Initilizates a keyboard driver
*/
void init_keyboard(){
    printf("Initialization a keyboard...\n");

    bool isKeyboard = firefly::drivers::ps2::init();
    io::legacy::writeTextSerial("Keyboard Driver returned %d\n\n", (isKeyboard) ? 1 : 0);
}

ACPITable acpitable;

/*
    Kernel
*/
void kernel_main() {
    applications::registerApplications();
    firefly::drivers::pit::init();
    firefly::kernel::cpuid::get_model();
    if(firefly::kernel::cpuid::check_apic() == 512){
        printf("APIC is supported\n");
        RSDPDescriptor20 *rsdpd = firefly::drivers::acpi::find_acpi();
        if(rsdpd == nullptr){
            trace::panic(trace::PM_RSDP_NOT_FOUND, trace::PC_RSDP_NOT_FOUND);
        }
        acpitable = firefly::drivers::acpi::parse_table(rsdpd);
        if(acpitable.FADTable->PMTimerLength == 4){
            printf("APIC Timer is supported\n");
        } else {
            printf("APIC Timer is not supported. Software multitasking will be used.");
        }
    } else {
        trace::panic(trace::PM_ACPI_NOT_SUPPORTED, trace::PC_ACPI_NOT_SUPPORTED);
    }
    write_ff_info();
    init_keyboard();
    //firefly::kernel::io::mouse::init(); 
    firefly::drivers::pit::timer_phase(1000, PIT_COUNTER1, PIT_MODE_HARDWARE_RETRIGGER);                
    printf("\n> ");

    for(;;){
        firefly::drivers::ps2::handle_input();
    }
}
}  // namespace firefly::kernel::main