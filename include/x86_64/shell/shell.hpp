#pragma once

#include "color.hpp"
#include "gui/gui.hpp"
#include <x86_64/pmp/mp.hpp>
#include <x86_64/applications/shell/etc.hpp>

struct layer {
    uint8_t action; //image, cube, rectangle or text
    int x; //image, cube, rectangle, text
    int y; //image, cube, rectangle, text
    int size; //cube
    int sizex; //rectangle
    int sizey; //rectangle
    int gbar_color; //pixel, cube, rectangle, text
    unsigned long long speed; //cube, rectangle, text, image
    char *text; //text
    sbif *sbif; //image

    uint8_t is_used;
    uint8_t draw;
    char *nid;
    uint8_t draw2img = 0;
};
struct mouse_handle {
    void (*handler)();
    bool is_used;
    layer *l;
};

namespace firefly::kernel::shell {
    inline bool xydtest(layer *l){
        if(l->x < 0 || l->y < 0) return false;
        if(l->draw == 0) return false;
        if(l->is_used == 0) return false;
        return true;
    }
    inline bool l1_lays_on_l2(layer *l1, layer *l2){
        if(l1->x > l2->x && l1->x < (l2->x + l2->sizex) && l1->y > l2->y && l1->y < (l2->y + l2->sizey)) return true;
        return false;
    }
}