#include <ncurses.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include "graphics.h"

graphics::graphics() {
    scale_factor = 1;
    screenSize = {0, 0};
    currentScreen = 0;
}

graphics::screen_size graphics::init() {
    int max_y = 0, max_x = 0;

    initscr();
   	clear();
    noecho();
    cbreak();

    curs_set(false);

    getmaxyx(stdscr, max_y, max_x);

    screenSize.max_x = max_x;
    screenSize.max_y = max_y;

    // printw("Seems that you can use ncurses ...\nPress any key to exit!");


    // refresh();

    // getch();

    //printf("%d %d\n", max_x, max_y);

    screen_size s = { max_x, max_y };
    return s;
}

void graphics::initColor() {
    if (has_colors())
    {
        start_color();
    
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);

        // flipped

        init_pair(8, COLOR_BLACK,   COLOR_RED);
        init_pair(9, COLOR_BLACK,   COLOR_GREEN);
        init_pair(10, COLOR_BLACK,   COLOR_YELLOW);
        init_pair(11, COLOR_BLACK,   COLOR_BLUE);
        init_pair(12, COLOR_BLACK,   COLOR_CYAN);
        init_pair(13, COLOR_BLACK,   COLOR_MAGENTA);
        init_pair(14, COLOR_BLACK,   COLOR_WHITE);
    }
}

void graphics::setColor(unsigned int c) {
    if (c > 14 || c == 0) {
        throw ERR_INVALID_COLOR;
    }

    attrset(COLOR_PAIR(c));
}

void graphics::sleep(unsigned int t) {
    usleep(t);
}

void graphics::refreshDisplay() {
    refresh();
}

void graphics::setScaleFactor(double d) {
    scale_factor = d;
}

void graphics::drawPoint(double x, double y, char c) {
    //attrset(COLOR_PAIR(3));

    x *= (scale_factor * 3.0 * 5.0/6.0);
    y *= scale_factor;

    x += screenSize.max_x / 2;
    y += screenSize.max_y / 2;

    //std::cerr << "x = " << (int)x << ", y = " << (int)y << '\n';

    mvaddch((int) y, (int) x, c);
}

void graphics::end() {
    endwin();
}
