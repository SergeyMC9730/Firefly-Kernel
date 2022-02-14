#include <x86_64/fs/custom/main.hpp>
#include <stl/cstdlib/cstring.h>
#include <x86_64/random.hpp>

namespace firefly::kernel::fs::custom {
    filesystem_t filesystem;
    void init(const char *name){
        uint8_t i = 0;
        while(i < 64 && name[i] != 0){
            filesystem.name[i] = name[i];
            i++;
        }
        return;
    }
    file_t *make_file(const char *name, int format){
        //find free file slot
        uint16_t i = 0;
        while(i < 1024 && filesystem.files[i].is_used == 1) {
            if(i == 1023 && filesystem.files[i].is_used == 1) return nullptr;
            i++;
        }
        //rename file
        uint16_t fslot = i;
        i = 0;
        while(i < 64 && name[i] != 0){
            filesystem.files[fslot].name[i] = name[i];
            i++;
        }
        filesystem.file_count++;
        filesystem.files[fslot].id = firefly::kernel::randomizer::rand();
        filesystem.files[fslot].format = format;
        filesystem.files[fslot].is_used = 1;
        
        return &filesystem.files[fslot]; 
    }
    void remove_file(int id){
        filesystem.files[id % UINT8_MAX].is_used = 0;
        return;
    }
    file_t *make_folder(const char *name){
        file_t *res = make_file(name, 2);
        res->flags[0] = 1;
        
        return res;
    }
}