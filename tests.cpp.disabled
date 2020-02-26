#include "vector.h"
#include "state.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include "graphics/graphics.h"
#include <unistd.h>
#include <ncurses.h>


void testGroup0() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256); // sun's radius in AU
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5); // earth's radius in AU

    sys.printOut();
}

void testGroup1_Euler1() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    for (double i = 0; i < PI; i += h) {
        sys.euler1();
    }

    std::cout << "Final Result:\n";
    sys.printOut();

}

void testGroup2_KickStep1() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    for (double i = 0; i < PI; i += h) {
        sys.kickStep1();
        //sys.printOut();
    }

    std::cout << "Final Result:\n";
    sys.printOut();

}

void testGroup3_RK4() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    for (double i = 0; i < PI; i += h) {
        #if DEBUG
        std::cout << "i = " << i << "\n";
        #endif

        sys.rk4();

        #if DEBUG
        sys.printOut();
        #endif
    }

    std::cout << "Final Result:\n";
    sys.printOut();
}

void testGroup4_Energy(const int orbits) {
    double h = 1e-2;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    for (double i = 0; i < orbits * PI * 2; i += h) { // orbits * 2 * PI

        sys.kickStep1();

        //printf("t = %.3f; E = %e\n", i, sys.computeEnergy());

        //printf("%.3f\t%e\n", i, sys.computeEnergy());
    }

    //std::cout << "Final Result:\n";
    //sys.printOut();
}

void testGroup5_Graphics(const int orbits) {
    double h = 1e-2;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    graphics::screen_size s = graphics::init();
    int min = s.max_x;
    if (s.max_y < min) {
        min = s.max_y;
    }

    double factor = min / 2.5;

    graphics::setScaleFactor(factor);

    for (double i = 0; i < orbits * PI * 2; i += h) { // orbits * 2 * PI
        //clear();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            graphics::drawPoint(sys[i], sys[i + 1], '.');
        }

        sys.kickStep1();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            graphics::drawPoint(sys[i], sys[i + 1], 'o');
        }
        refresh();

        usleep(10000);
    }

    graphics::end();
}

void testGroup5_1_PyGraphics(const int orbits) {
    double h = 1e-2;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1, 0.00465479256);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8, 4.25879793e-5);

    std::ofstream pipe;
    std::cerr << "Opening pipe...\n";
    pipe.open("graphics.socket");

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    double factor = 500 / 2.5;

    pipe << "set-scale-factor:" << factor << '\n';
    
    for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
        pipe << "new:[" << i << ',' << sys[i] << ',' << sys[i+1] << ',' << 10 << "]\n";
    }

    for (double i = 0; i < orbits * PI * 2; i += h) { // orbits * 2 * PI

        sys.kickStep1();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            pipe << "mv:[" << i << ',' << sys[i] << ',' << sys[i+1] << ',' << 10 << "]\n";
        }

        usleep(10000);
    }

    pipe.close();
}

void testGroup6_Collision() {
    double h = 1e-7;
    State sys(h);

    sys.addBody(-10e-5, 0, 0, 0, 0, 0, 1e-2, 4.25879793e-5);
    sys.addBody(10e-5, 0, 0, 0, 0, 0, 1e-2, 4.25879793e-5);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    graphics::screen_size s = graphics::init();
    int min = s.max_x;
    if (s.max_y < min) {
        min = s.max_y;
    }

    double factor = min / (1e-4 * 2.5);

    graphics::setScaleFactor(factor);

    for (double i = 0; i < 100 * PI * 2; i += h) {
        //clear();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            graphics::drawPoint(sys[i], sys[i + 1], '.');
        }

        sys.rk4();

        for (unsigned int i = 0; i < sys.size() * 6; i += 6) {
            graphics::drawPoint(sys[i], sys[i + 1], 'a' + i/6);
        }
        refresh();

        usleep(50000);
    }

    graphics::end();
}

int main() {
    std::cerr << "Starting...\n";

    //try
    //{
    testGroup6_Collision();
    /*}
    catch(const int& e)
    {
        if (e == ERR_VECTOR_SIZE_MISMATCH) {
            std::cerr << "ERR_VECTOR_SIZE_MISMATCH\n";
        }
        else if (e == ERR_VECTOR_OUT_OF_BOUNDS) {
            std::cerr << "ERR_VECTOR_OUT_OF_BOUNDS\n";
        }
        else {
            std::cerr << e << '\n';
        }
    }*/
  
  
    std::cerr << "Done\n";
    return 0;
}
