#include "vector.h"
#include "state.h"
#include <cstdio>
#include <iostream>

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

int main() {
    std::cerr << "Starting...\n";

    //try
    //{
    testGroup4_Energy(1);
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
