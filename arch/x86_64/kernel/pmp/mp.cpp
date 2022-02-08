//pceudo multiprocessing

#include <x86_64/pmp/mp.hpp>
#include <x86_64/drivers/serial_legacy.hpp>
#include <x86_64/random.hpp>
#include <x86_64/registers.hpp>
#include <x86_64/drivers/ports.hpp>

using namespace firefly::kernel::io;

namespace firefly::kernel::mp {
    int aa = 0;
    bool work = true;
    Process processes[0xFF];
    bool has_updated = false;

    uint8_t make(void (*func)(Process *process), unsigned char run_one_time, char *nid) {
        //search free processes
        unsigned char i = 0;
        while(processes[i].used) i++;

        
        //use process
        processes[i].used = 1;
        processes[i].onetime = run_one_time;
        processes[i].func = func;
        processes[i].block = firefly::mm::greenleafy::use_block(0);
        processes[i].nid = nid;
        processes[i].called_times = 0;

        has_updated = true;

        return i;
    }
    uint8_t make(void (*func)(Process *process), unsigned char run_one_time){
        uint8_t id = make(func, run_one_time, (char *)"unknown process");
        firefly::kernel::io::legacy::writeTextSerial("Warning: process %d with unknown name id was made.\n", id);
        return id;
    }

    void run(){
        if(!work) return;
        firefly::kernel::randomizer::srand(firefly::kernel::registers::get().u32.ebx);
        
        uint8_t list[0xFE];

        unsigned char i = 0;
        unsigned char i2 = 0;
        while(true) {
            if(has_updated) {
                has_updated = false;
                i = 0;
                i2 = 0;
                while(i < 0xFE){
                    if(processes[i].used) {
                        list[i2] = i;
                        i2++;
                    }
                    i++;
                }
            }
            uint8_t id2use = inb(0x40) % i2;
            // if(processes[i].used == 1 && i != 0xFF) {
            //     processes[i].func(&processes[i]);
            //     processes[i].called_times++;
            //     if(processes[i].onetime == 1) {
            //         processes[i].used = 0;
            //         firefly::mm::greenleafy::delete_block(processes[i].block->block_number);
            //     } 
            // }
            if(processes[list[id2use]].used == 1 && list[id2use] != 0xFF) {
                processes[list[id2use]].func(&processes[list[id2use]]);
                processes[list[id2use]].called_times++;
                if(processes[list[id2use]].onetime == 1) close(list[id2use]);
            }
            i++;
        }
    }
    void turn_off(){
        work = false;
    }
    void turn_on(){
        work = true;
    }
    void close(uint8_t id){
        if(!processes[id].used) return;
        processes[id].used = 0;
        firefly::mm::greenleafy::delete_block(processes[id].block->block_number);
        return;
    }
    void clear(){
        uint8_t i = 0;
        while(i < 0xFF) close(i++);
    }
}