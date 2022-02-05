#include <x86_64/random.hpp>
#include <stl/cstdlib/stdio.h>

namespace firefly::kernel::randomizer {
    namespace experimental {
        [[maybe_unused]] static inline bool test(){
            return true;
        }
    }
    unsigned long int next = 1;
    int rand(){
        next = next * 0x41c64e76 + 12345;

        return (unsigned int)(next / 65536) % 32768;
    }

    void srand(unsigned int seed){
        next = seed;
    }

    uint64_t rdseed(uint64_t a) {
        uint64_t result = 0;
        result += (a - a);
        asm("movq $0x64, %%rcx\n\t"
            ".retry:\n\t"
            "   rdseedq %%rax\n\t"
            "   jc .done\n\t"
            "   loop .retry\n\t"
            ".fail:\n\t"
            "   movq $0x00, %%rax\n\t"
            "   movq %%rax, %0\n\t"
            ".done:\n\t"
            "   movq %%rax, %0\n\t"
            : "=a" (result)
        );
        return result;
    }
    uint32_t rdseed(uint32_t b) {
        uint32_t result = 0;
        result += (b - b);
        asm("movl $0x64, %%ecx\n\t"
            ".retryl:\n\t"
            "   rdseedl %%eax\n\t"
            "   jc .donel\n\t"
            "   loop .retryl\n\t"
            ".faill:\n\t"
            "   movl $0x00, %%eax\n\t"
            "   movl %%eax, %0\n\t"
            ".donel:\n\t"
            "   movl %%eax, %0\n\t"
            : "=a" (result)
        );
        return result;
    }
    uint16_t rdseed(uint16_t c) {
        uint16_t result = 0;
        result += (c - c);
        asm("movw $0x64, %%cx\n\t"
            ".retryw:\n\t"
            "   rdseedw %%ax\n\t"
            "   jc .donew\n\t"
            "   loop .retryw\n\t"
            ".failw:\n\t"
            "   movw $0x00, %%ax\n\t"
            "   movw %%ax, %0\n\t"
            ".donew:\n\t"
            "   movw %%ax, %0\n\t"
            : "=a" (result)
        );
        return result;
    }
}