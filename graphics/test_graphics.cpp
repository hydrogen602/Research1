#include "graphics.h"
#include "screenState.h"
#include <ncurses.h>

#include <iostream>

#define NOPE 123

void test1() {
    graphics g;

    g.init();

    g.setScaleFactor(1, 0);

    g.drawPoint(0, 0, 'X', 0);

    getch();

    g.end();
}

void test2() {
    char c = 0;

    screenState s(10, 6);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 6; ++j) {
            s.setPixel(i, j, pixel{c++, 1});
        }
    }

    c = 0;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 6; ++j) {
            pixel p = s.getPixel(i, j);
            if (p.character != c++) {
                throw NOPE;
            }
        }
    }

    std::cout << "Test 2 Done\n";
}

int main() {
    test2();
}