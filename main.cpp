#include "vector.h"
#include "state.h"
#include <cstdio>
#include <iostream>
#include "graphics/graphics.h"
#include <ncurses.h>

void collision() {
    double h = 1e-7;
    State sys(h);

    sys.addBody(-10e-5, 0, 0, 0, 0, 0, 1e-2, 4.25879793e-5);
    sys.addBody(10e-5, 0, 0, 0, 0, 0, 1e-2, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    graphics g;

    graphics::screen_size s = g.init();
    int min = s.max_x;
    if (s.max_y < min) {
        min = s.max_y;
    }

    double factor = min / (1e-4 * 2.5);

    g.setScaleFactor(factor);

    g.initColor();

    for (double i = 0; i < 100 * PI * 2; i += h) {
        //clear();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            g.setColor(i/6 + 2);
            g.drawPoint(sys[i], sys[i + 1], '.');
        }

        sys.rk4();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            g.setColor(i/6 + 2);
            g.drawPoint(sys[i], sys[i + 1], 'o');
        }

        double totalE = sys.computeEnergy();
        
        mvprintw(0, 0, "Energy = %e", totalE);

        g.refreshDisplay();

        g.sleep(10000);
    }

    g.end();
}

int main() {
    collision();
    return 0;
}