#include <x86_64/cpuid/cpuid.hpp>

namespace firefly::kernel::cpuid {
    int get_model() {
        int ebx, e;
        __cpuid(0, e, ebx, e, e);
        //firefly::kernel::io::legacy::writeTextSerial("get_model() %d\n", ebx);
        return ebx;
    }
    int check_apic() {
        unsigned int eax, e, edx;
        __get_cpuid(1, &eax, &e, &e, &edx);
        firefly::kernel::io::legacy::writeTextSerial("check_apic() %d\n", edx & (1 << 9));
        return edx & (1 << 9);
    }
    int check_rdseed(){
        int result;
        asm("movl $0x07, %%eax\n\t"
            "movl $0x00, %%ecx\n\t"
            "cpuid \n"
            "shrl $0x12, %%ebx\n\t"
            "andl $0x01, %%ebx\n\t"
            "jz rdseeda\n\t"
            "jnz rdseedn\n\t"
            "rdseeda:\n\t"
            "   movl $0x01, %%ebx\n\t"
            "   movl %%ebx, %0\n\t"
            "rdseedn:\n\t"
            "   movl $0x00, %%ebx\n\t"
            "   movl %%ebx, %0"
            : "=b" (result)
        );
        firefly::kernel::io::legacy::writeTextSerial("check_rdseed %d\n", result);
        return result;
    }

}