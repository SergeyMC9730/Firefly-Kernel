#pragma once
namespace firefly::kernel::fs::custom {
    namespace formats {
        constexpr int no_format = 0;
        constexpr int text = 1;
        constexpr int folder = 2;
    }
    #pragma pack(push, 1)
    typedef struct {
        int linked[1024];
    } directory_t;
    typedef struct {
        int id;
        int size = 0;
        char name[64];
        char *data;
        bool is_used;
        int format;
        char flags[8];
        directory_t dir;
    } file_t;
    typedef struct {
        char name[64];
        int file_count = 0;  
        file_t files[1024];
    } filesystem_t;
    #pragma pack(pop)

    extern filesystem_t filesystem;
    void init(const char *name);
    file_t *make_file(const char *name, int format);
    void remove_file(int id);
}