#include <stl/cstdlib/stdio.h>
#include <x86_64/fs/custom/main.hpp>
#include <x86_64/applications/writefile/main.hpp>
#include <x86_64/drivers/ps2.hpp>
#include <x86_64/fs/custom/main.hpp>
#include <x86_64/memory-manager/malloc.hpp>

namespace firefly::applications::writefile {
    char finm_b[64];
    char data_b[65536];
    uint8_t mode = 0;
    uint8_t current_key;
    uint8_t buf;
    uint16_t chars = 0;
    void keyboard_handle(){
        switch(mode){
            case 0: {
                if(current_key != 0 && current_key != 10){
                    finm_b[buf] = current_key;
                    buf++;
                }
                return;
            }
            case 1: {
                if(current_key != 0 && current_key != 10){
                    data_b[buf] = current_key;
                    chars++;
                    buf++;
                }
                return;
            }
        }
        
    }
    int writefile_main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
        uint16_t i = 0;
        buf = 0;
        chars = 0;
        current_key = 0;
        while(i < 0x40) {
            data_b[i] = 0;
            finm_b[i++] = 0;
        }
        while(i < (0xFFFF - 0x40)) data_b[i++] = 0;
        printf("[Writefile] Please, enter name of file:\n> ");
        firefly::drivers::ps2::redirect_to_app(keyboard_handle, &current_key);
        while(current_key != 10){
            current_key = 0;
            firefly::drivers::ps2::app_input();
        }
        mode = 1;
        current_key = 0;
        buf = 0;
        printf("[Writefile] Please, enter data of file:\n> ");
        firefly::drivers::ps2::redirect_to_app(keyboard_handle, &current_key);
        while(current_key != 10){
            current_key = 0;
            firefly::drivers::ps2::app_input();
        }
        current_key = 0;
        buf = 0;
        i = 0;
        firefly::kernel::fs::custom::file_t *result = firefly::kernel::fs::custom::make_file(finm_b, 0);
        char *data_alloc = (char*)firefly::mm::smalloc::smalloc(chars).address;
        while(i < chars){
            data_alloc[i] = data_b[i];
            data_b[i] = 0;
            i++;
        }
        result->data = data_alloc;
        result->size = chars;
        current_key = 0;
        buf = 0;
        i = 0;
        mode = 0;
        while(i < 0x40) {
            finm_b[i++] = 0;
        }
        printf("[Writefile] Done.\n");
        return 0;
    }

    int getc(){ return 1855568; }
}