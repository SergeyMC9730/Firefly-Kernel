#include <stl/cstdlib/stdio.h>
#include <stl/cstdlib/cstdint.h>
#include <x86_64/applications/test/main.hpp>
#include <x86_64/kernel.hpp>
#include <x86_64/drivers/ports.hpp>

namespace firefly::applications::shutdown {
    int memcmp3(const char *s1, const char *s2, int n) {
        int index = 0;
        while (s1[index] && s2[index] && s1[index] == s2[index] && n--)
            index++;

        if (n == 0)
            return 0;
        else
            return s1[index] - s2[index];
    }

    int shutdown_main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){;
        const char VBOX[4] = {'V', 'B', 'O', 'X'};
        const char BOCHS[5] = {'B', 'O', 'C', 'H', 'S'};
        
        if(memcmp3(VBOX, firefly::kernel::main::acpitable.RSDP->firstPart.OEMID, 4)) {
            firefly::kernel::io::outb(0x4004, 0x34);
            firefly::kernel::io::outb(0x4004, 0x00);
        } else if(memcmp3(BOCHS, firefly::kernel::main::acpitable.RSDP->firstPart.OEMID, 5)) {
            firefly::kernel::io::outb(0x604, 0x20);
            firefly::kernel::io::outb(0x604, 0x00);
        } else {
            printf("Unable to shutdown the system: Invalid OEMID. Try to shutdown on Virtualbox or QEMU\n");
            return -1;
        }    

        return 0;
    }

    int getc(){ return 1738420; }
}