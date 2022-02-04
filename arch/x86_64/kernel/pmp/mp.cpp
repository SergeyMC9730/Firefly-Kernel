//pceudo multiprocessing

#include <x86_64/pmp/mp.hpp>
#include <x86_64/drivers/serial_legacy.hpp>
#include <x86_64/random.hpp>
#include <x86_64/registers.hpp>

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
        
        unsigned char i = 0;

        while(true) {
            //firefly::kernel::io::legacy::writeTextSerial("%d ", id2run);
            if(processes[i].used == 1) {
                processes[i].func(&processes[i]);
                if(processes[i].onetime == 1) close(i);   
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