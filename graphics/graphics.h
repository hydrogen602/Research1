#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <ncurses.h>

namespace graphics {
    typedef struct screen_size_container {
        int max_x;
        int max_y;
    } screen_size;

    screen_size init();

    void end();

    void setScaleFactor(double d);

    void drawPoint(double x, double y, char c);
}

#endif