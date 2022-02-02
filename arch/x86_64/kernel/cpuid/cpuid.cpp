#include <x86_64/cpuid/cpuid.hpp>

namespace firefly::kernel::cpuid {
    int get_model() {
        int ebx, e;
        __cpuid(0, e, ebx, e, e);
        firefly::kernel::io::legacy::writeTextSerial("get_model() %d\n", ebx);
        return ebx;
    }
    int check_apic() {
        unsigned int eax, e, edx;
        __get_cpuid(1, &eax, &e, &e, &edx);
        firefly::kernel::io::legacy::writeTextSerial("check_apic() %d\n", edx & (1 << 9));
        return edx & (1 << 9);
    }
}