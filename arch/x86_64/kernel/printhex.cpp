#include <x86_64/printhex.hpp>

using namespace firefly::kernel::io::legacy;

namespace firefly::kernel {
    void print_ramdata(char *p, uint64_t size) {
        uint64_t i = 0;
        writeTextSerial("---- MEMORY DUMP START ----\n\n");
        while(i < size){
            uint8_t ii = 0;
            while(ii < 32){
                writeTextSerial("%c ", (p[i] == '\n') ? '?' : p[i]);
                i++;
                ii++;
            }
            ii = 0;
            writeTextSerial("\n");
        }
        writeTextSerial("\n---- MEMORY DUMP END ----\n");
    }
}