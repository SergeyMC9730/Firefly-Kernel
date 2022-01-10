#pragma once

#include <x86_64/drivers/vbe.hpp>
#include <x86_64/sleep.hpp>
#include <x86_64/applications/shell/etc.hpp>
#include <x86_64/memory-manager/greenleafy.hpp>

namespace firefly::kernel::shell::gui {
    inline void make_rectangle(int x, int y, int sizex, int sizey, int gbar_color, unsigned long long speed, uint8_t draw2img, sbif *image){
        int i = x;
        int i0 = y;
        switch(draw2img){
            case 0: {
                while(i < x + sizex){ //x
                    while(i0 < y + sizey){ //y
                        firefly::drivers::vbe::put_pixel(i, i0, gbar_color);
                        i0++;
                    }
                    i++;
                    i0 = y;
                    if(speed != 0) firefly::kernel::sleep::sleep(speed);
                }
                break;
            }
            case 1: {
                while(i < x + sizex){ //x
                    while(i0 < y + sizey){ //y
                        image->buffer[image->sizex * (y - 1) + (x + 1) - 1] = gbar_color;
                        i0++;
                    }
                    i++;
                    i0 = y;
                    if(speed != 0) firefly::kernel::sleep::sleep(speed);
                }
                break;
            }
        }
        return;
    }

    inline void make_cube(int x, int y, int size, int gbar_color, unsigned long long speed, uint8_t draw2img, sbif *image){
        make_rectangle(x, y, size, size, gbar_color, speed, draw2img, image);
        return;
    }
    inline void make_text(const char *text, int x, int y, int gbar_color, unsigned long long speed){
        int i = 0;
        int xx = x;
        int yy = y;
        while (text[i] != 0) {
            switch(text[i]){
                case '\n': {
                    yy += 16;
                    xx = x;
                    break;
                }
                case '\t': {
                    xx += 4;
                    break;
                }
                case '\b': {
                    xx -= 8;
                    break;
                }
                default: {
                    xx += 8;
                    break;
                }
            }
            firefly::drivers::vbe::putc(text[i++], xx, yy, gbar_color);
            if(speed != 0) firefly::kernel::sleep::sleep(speed);
        }
    }
    inline window *make_window(const char *name){
        firefly::applications::shell::etc::Window.window_data->sizex = 927;
        firefly::applications::shell::etc::Window.window_data->sizey = 463;
        firefly::applications::shell::etc::Window.window_data->x = 56;
        firefly::applications::shell::etc::Window.window_data->y = 142;
        firefly::applications::shell::etc::Window.window_data->buffer = (int*)firefly::mm::greenleafy::use_block(0)->block;
        int i = 0;
        while(name[i] != 0){
            firefly::applications::shell::etc::Window.name[i] = name[i];
            i++;
        }
        return &firefly::applications::shell::etc::Window;
    }
}