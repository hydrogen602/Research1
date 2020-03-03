#include "vector.h"
#include "state.h"
#include <cstdio>
#include <iostream>
#include "graphics/graphics.h"
#include <ncurses.h>

void collision() {
    graphics g;

    graphics::screen_size s = g.init();
    int min = s.max_x;
    if (s.max_y < min) {
        min = s.max_y;
    }

    std::cerr << "Survived g.init\n";

    g.newScreenState();

    std::cerr << "Survived new screen" << std::endl;

    double factor = min / (1e-4 * 15); // 45

    g.setScaleFactor(factor, 0);

    std::cerr << "Survived setting scale factor" << std::endl;

    double h = 1e-7;
    State sys(h, s.max_x/2.0 / (factor * 3.0 * 5.0/6.0), s.max_y/2.0 / (factor));

    sys.addBody(-30e-5, 0, 0, 0, 5, 0, 1e-2, 4.25879793e-5);
    sys.addBody(30e-5, 0, 0, 0, 0, 0, 1e-2, 4.25879793e-5);
    sys.addBody(0, 35e-5, 0, 5, 0, 0, 1e-2, 4.25879793e-5);
    sys.addBody(0, -35e-5, 0, -5, 0, 0, 1e-2, 4.25879793e-5);

    sys.addBody(-30e-5, 35e-5, 0, 0, 5, 0, 1e-2, 4.25879793e-5);
    sys.addBody(30e-5, -35e-5, 0, 2, 2, 0, 1e-2, 4.25879793e-5);
    sys.addBody(30e-5, 35e-5, 0, 5, 0, 0, 1e-2, 4.25879793e-5);
    //sys.addBody(-30e-5, -35e-5, 0, -5, 0, 0, 1e-2, 4.25879793e-5);

    //sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256);
    // sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    g.initColor();

    std::cerr << "Survived init" << std::endl;

    int chartLoc = -s.max_x / 2 - 1;
    const int chartSkip = 2;
    int currChartSkip = 0;

    for (double i = 0; i < 100 * PI * 2; i += h) {
        //clear();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            g.setColor(i/6 + 1);
            g.drawPoint(sys[i], sys[i + 1], '.', 0);
        }

        sys.kickStep1();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            g.setColor(i/6 + 1);
            g.drawPoint(sys[i], sys[i + 1], 'o', 0);
        }

        double totalE = sys.computeEnergy();

        if (currChartSkip <= 0) {
            currChartSkip = chartSkip;

            // chart!
            // turn 0 to 5e-1 to 0 to 50

            double chartScale = s.max_y / 10e-1;
            int chartY = totalE * -chartScale - s.max_y / 2.0;


            //int chartY = s.max_y / 2.0 - totalE * 1;

            //std::cerr << "chartY = " << chartY << '\n';

            if (chartLoc >= s.max_x / 2) {
                // slide everything to the left one
                g.shiftPixelsLeft(1, 1);
                if (g.getCurrentScreen() == 1) {
                    g.setScreenRelNoThrow(0);
                }
                
            }
            else {
                ++chartLoc;
            }
            g.setColor(WHITE_ON_BLACK);
            g.drawPoint(chartLoc, chartY, '-', 1);
        }
        --currChartSkip;

        g.setColor(WHITE_ON_BLACK);
        
        mvprintw(0, 0, "Energy = %e", totalE);
        mvprintw(1, 0, "Screens = %d", g.countScreens());
        mvprintw(2, 0, "Current Screen = %d", g.getCurrentScreen());

        mvprintw(s.max_y - 1, 0, "Press any key to close");

        g.refreshDisplay();

        int c = g.sleepInterruptible(5); // returns 0 on no char typed

        if (c == 'd') {
            g.setScreenRelNoThrow(1);
        }
        else if (c == 'a') {
            g.setScreenRelNoThrow(-1);
        }
        else if (c > 0) {
            std::cerr << "c = " << c << '\n';
            break; // close program if any key is hit
        }
    }

    std::cerr << "Survived run\n";

    g.end();
}

int main() {
    collision();
    return 0;
}