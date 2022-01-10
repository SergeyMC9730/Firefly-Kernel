#pragma once

struct sbif {
    int *buffer;
    int x;
    int y;
    int sizex;
    int sizey;
};
struct window {
    char *name;
    sbif *window_data;
};

namespace firefly::applications::shell::etc {
    extern window Window;
}