#include <ncurses.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include "graphics.h"

graphics::graphics() {
    //scale_factor = 1;
    screenSize = {0, 0};

    currentColor = WHITE_ON_BLACK;

    currentScreen = 0;

    //screens = new screenState[maxScreens];
}

void graphics::newScreenState() {
    std::cerr << "Survived new screen\n";
    screens.push_back(screenState(screenSize.max_y, screenSize.max_x));
    std::cerr << "Survived new screen push\n";
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

    screens.push_back(screenState(max_y, max_x));

    // printw("Seems that you can use ncurses ...\nPress any key to exit!");


    // refresh();

    // getch();

    //printf("%d %d\n", max_x, max_y);

    graphics::screen_size s = { max_x, max_y };

    // make screens

    return s;
}

void graphics::initColor() {
    if (has_colors())
    {
        start_color();
    
        init_pair(RED_ON_BLACK, COLOR_RED,     COLOR_BLACK);
        init_pair(GREEN_ON_BLACK, COLOR_GREEN,   COLOR_BLACK);
        init_pair(YELLOW_ON_BLACK, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(BLUE_ON_BLACK, COLOR_BLUE,    COLOR_BLACK);
        init_pair(CYAN_ON_BLACK, COLOR_CYAN,    COLOR_BLACK);
        init_pair(MAGENTA_ON_BLACK, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(WHITE_ON_BLACK, COLOR_WHITE,   COLOR_BLACK);

        // flipped

        init_pair(BLACK_ON_RED, COLOR_BLACK,   COLOR_RED);
        init_pair(BLACK_ON_GREEN, COLOR_BLACK,   COLOR_GREEN);
        init_pair(BLACK_ON_YELLOW, COLOR_BLACK,   COLOR_YELLOW);
        init_pair(BLACK_ON_BLUE, COLOR_BLACK,   COLOR_BLUE);
        init_pair(BLACK_ON_CYAN, COLOR_BLACK,   COLOR_CYAN);
        init_pair(BLACK_ON_MAGENTA, COLOR_BLACK,   COLOR_MAGENTA);
        init_pair(BLACK_ON_WHITE, COLOR_BLACK,   COLOR_WHITE);
    }
}

void graphics::setColor(char c) {
    if (c > 14 || c == 0) {
        throw ERR_INVALID_COLOR;
    }

    attrset(COLOR_PAIR(c));
    currentColor = c;
}

void graphics::sleep(unsigned int t) {
    usleep(t);
}

int graphics::sleepInterruptible(unsigned int t) {
    timeout(t);
    int c = getch();
    if (c == ERR) {
        return 0;
    }
    return c;
}

void graphics::refreshDisplay() {
    refresh();
}

void graphics::setScaleFactor(double d, int screen) {
    std::cerr << "currentScreen = " << currentScreen << std::endl;
    screens[currentScreen].setScaleFactor(d);
}

void graphics::drawPoint(double x, double y, char c, int screen) {
    if (screen < 0 || screen > screens.size()) {
        throw ERR_VECTOR_OUT_OF_BOUNDS;
    }
    double scale_factor = screens[screen].getScaleFactor();

    if (scale_factor != 1) {
        x *= scale_factor * 3.0 * 5.0/6.0;
        y *= scale_factor;
    }

    x += screenSize.max_x / 2;
    y += screenSize.max_y / 2;

    int xInt = (int)x;
    int yInt = (int)y;

    try {
        screens[screen].setPixel(yInt, xInt, pixel{c, currentColor});
    }
    catch (int e) {
        if (e == ERR_VECTOR_OUT_OF_BOUNDS) {
            //std::cerr << "Something went off-screen\n";
        }
        else {
            throw;
        }
    }
    

    if (screen == currentScreen) {
        drawPoint(xInt, yInt, c);
    }
}

void graphics::drawPoint(int x, int y, char c) {
    //attrset(COLOR_PAIR(3));

    //std::cerr << "x = " << (int)x << ", y = " << (int)y << '\n';

    mvaddch((int) y, (int) x, c);
}

void graphics::end() {
    endwin();
}

void graphics::setScreenRelNoThrow(int i) {
    i = currentScreen + i;

    if (i < 0 || i >= screens.size()) {
        return;
    }
    std::cerr << "graphics::setScreenNoThrow -> i = " << i << '\n';
    setScreen(i);
}

void graphics::setScreen(int i) {
    if (i < 0 || i >= screens.size()) {
        throw ERR_VECTOR_OUT_OF_BOUNDS;
    }
    currentScreen = i;

    std::cerr << "graphics::setScreen -> currentScreen = " << currentScreen << '\n';

    clear();

    for (int row = 0; row < screenSize.max_y; ++row) {
        for (int col = 0; col < screenSize.max_x; ++col) {
            //std::cerr << "row = " << row << "; col = " << col << '\n';
            pixel p = screens[currentScreen].getPixel(row, col);
            attrset(COLOR_PAIR(p.color));
            drawPoint(col, row, p.character);
        }
    }

    std::cerr << "graphics::setScreen -> survived redrawing screen\n";

    refresh();
}

void graphics::shiftPixelsLeft(int shift, int screen) {
    screens[screen].shiftPixelsLeft(shift);
}

int graphics::countScreens() {
    return screens.size();
}

int graphics::getCurrentScreen() {
    return currentScreen;
}
