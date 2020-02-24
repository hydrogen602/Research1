#include "graphics.cpp"

int main() {
    init();

    setScaleFactor(1);

    drawPoint(0, 0);

    getch();

    end();
}