#include "vector.h"
#include "state.h"
#include <cstdio>
#include <cmath>
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
    State sys(h, s.max_x/2.0 / (factor * 3.0 * 5.0/6.0), s.max_y/2.0 / (factor), kDefault, 1e3);

    sys.addBody(-30e-5, 0, 0, 0, 0, 0, 1e-2, 4.25879793e-5);
    sys.addBody(30e-5, 0, 0, 0, 0, 0, 1e-2, 4.25879793e-5);
    //sys.addBody(0, 35e-4, 0, 5, 0, 0, 1e-2, 4.25879793e-4);
    //sys.addBody(0, -35e-4, 0, -5, 0, 0, 1e-2, 4.25879793e-4);

    //sys.addBody(-30e-5, 35e-5, 0, 0, 5, 0, 1e-2, 4.25879793e-5);
    //sys.addBody(30e-5, -35e-5, 0, 2, 2, 0, 1e-2, 4.25879793e-5);
    //sys.addBody(30e-5, 35e-5, 0, 5, 0, 0, 1e-2, 4.25879793e-5);
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


void collisionNoGraphics(double k, double drag) {

    const double h = 1e-7;
    std::cerr << "> k = " << k << ", drag = " << drag << '\n';
    State sys(h, 0, 0, k, drag);

    sys.addBody(-30e-7, 0, 0, 0, 0, 0, 1e-8, 4.25879793e-7);
    sys.addBody(30e-7, 0, 0, 0, 0, 0, 1e-8, 4.25879793e-7);
    //sys.addBody(0, 35e-4, 0, 5, 0, 0, 1e-2, 4.25879793e-4);
    //sys.addBody(0, -35e-4, 0, -5, 0, 0, 1e-2, 4.25879793e-4);

    //sys.addBody(-30e-5, 35e-5, 0, 0, 5, 0, 1e-2, 4.25879793e-5);
    //sys.addBody(30e-5, -35e-5, 0, 2, 2, 0, 1e-2, 4.25879793e-5);
    //sys.addBody(30e-5, 35e-5, 0, 5, 0, 0, 1e-2, 4.25879793e-5);
    //sys.addBody(-30e-5, -35e-5, 0, -5, 0, 0, 1e-2, 4.25879793e-5);

    //sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256);
    // sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    double totalE = sys.computeEnergy();
    std::cout << "initE: " << totalE << '\n';

    double s0 = sys.getSize(0);
    double s1 = sys.getSize(1);

    double lastIntersection = 0;
    bool approaching = false;
    bool deapproaching = false;


    vector3 v1 = sys.getVelocity(0);
    vector3 v2 = sys.getVelocity(1);

    double lastVel = 1;

    int runCounter = 0;
    for (double i = 0; i < /*10 * PI * 2 */ 1.0e-2; i += h) {
        runCounter++;

        sys.kickStep1();

        vector3 v1Next = sys.getVelocity(0);
        vector3 v2Next = sys.getVelocity(1);

        //std::cout << "v1 = <" << v1.x << ", " << v1.y << ", " << v1.z << ">, dot = " << v1.dot(v1Next) << '\n';

        vector3 diff = sys.getPosition(0) - sys.getPosition(1);
        double d = sqrt(diff.dot(diff));

        double deltaX = d - (s0 + s1);

        

        if (deltaX < 0) {
            // intersection
            if (!approaching) {
                std::cout << "flipped: " << i << ", " << lastVel << ", " << deltaX << std::endl;
                approaching = true;
            }

            //std::cout << "dx = " << deltaX << '\n';
            if (deltaX < lastIntersection) {
                lastIntersection = deltaX;
            }
            else if (!deapproaching) {
                deapproaching = true;
                std::cout << "intersection: " << i << ", " << fabs(deltaX / (s0 + s1)) * 100 << "%\n";
            }
        }
        else {
            if (deapproaching) {
                vector3 v = sys.getVelocity(0);
                double vel = sqrt(v.dot(v));

                std::cout << "flipped: " << i << ", " << vel << ", " << deltaX << std::endl;

                i = 1e100;
            }
            deapproaching = false;
            lastIntersection = 0;
        }

        vector3 v = sys.getVelocity(0);
        lastVel = sqrt(v.dot(v));

        if (v1.dot(v1Next) < 0) {
            if (v2.dot(v2Next) < 0) {
                // flip
                totalE = sys.computeEnergy();
                vector3 v = sys.getVelocity(0);
                double vel = sqrt(v.dot(v));

                //std::cout << "flipped: " << i << ", " << vel << ", " << deltaX << std::endl;
                
                //std::cerr << "flipped\n";
            }
            else {
                std::cerr << "only one flipped\n";
            }
        }
        else if (v2.dot(v2Next) < 0) {
            std::cerr << "only one flipped\n";
        }

        v2 = v2Next;
        v1 = v1Next;
    }
    std::cerr << "Survived run\n";
    std::cerr << "Runs: " << runCounter << '\n';
}

int main() {
    double k = kDefault;
    double drag = 1e3;

    std::cin >> k;
    std::cin >> drag;
    if (k == 0) {
        std::cerr << "Got a non floaty point\n";
        return 1;
    }
    // if (drag == 0) {
    //     std::cerr << "Got a non floaty point\n";
    //     return 1;
    // }

    collisionNoGraphics(k, drag);
    return 0;
}