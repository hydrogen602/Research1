#include <ncurses.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include "graphics.h"

int main() {
    graphics::init();

    graphics::initColor();

    printw("Seems that you can use ncurses ...\nPress any key to exit!\n");

    for (int n = 1; n <= 14; ++n) {
        attrset(COLOR_PAIR(n));
        printw("color %d\n", n);
    }

    refresh();

    getch();

    graphics::end();
}
