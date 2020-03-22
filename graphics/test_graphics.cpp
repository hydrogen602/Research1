#include "graphics.cpp"

int main() {
    graphics::init();

    graphics::setScaleFactor(1);

    graphics::drawPoint(0, 0, 'X');

    getch();

    graphics::end();
}