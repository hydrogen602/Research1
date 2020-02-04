#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include "body.h"

#include "test.cpp"

void findAcceleration(std::vector<Body> &system, double h) {
    for (int i = 0; i < system.size(); ++i) {
        vect3 accVector = {0, 0, 0};

        for (int j = 0; j < system.size(); ++j) {
            if (i != j) {
                double dSq = system[i].distanceSquaredFrom(system[j]);
                // a = g * m / r^2
                // g = 1
                // m = in solar masses

                double accScalar = system[j].mass / dSq; // magnitude of a
                vect3 dirUnitVec = system[i].unitVectTo(system[j]); // dir of a
                dirUnitVec.x *= accScalar;
                dirUnitVec.y *= accScalar;
                dirUnitVec.z *= accScalar;

                accVector.x += dirUnitVec.x;
                accVector.y += dirUnitVec.y;
                accVector.z += dirUnitVec.z; // i and j forces get calculated twice
            }
        }

        // found total acceleration

        // euler

        // printf("accVector = <%e, %e, %e>\n", accVector.x, accVector.y, accVector.z);

        system[i].integrate(accVector, h);
    }
}

void testGroup1() {
    std::vector<Body> sys;

    sys.push_back(Body{-1, 0, 0, 0, 0, 0, 0.0001});
    sys.push_back(Body{0, 1, 0, 0, 0, 0, 0.0001});

    std::cout << "N-body simulation\n";
    std::cout << "Number of bodies: " << sys.size() << '\n';

    double d = sys[0].distanceFrom(sys[1]);
    std::cout << "Distance test: " << d << '\n';
    test(compare(d, 1.4142135623730951));

    d = sys[0].distanceSquaredFrom(sys[1]);
    std::cout << "Distance squared test: " << d << '\n';
    test(compare(d, 2));

    printResult();
}

void testGroup2() {
    std::vector<Body> sys;

    sys.push_back(Body{0, 0, 0, 0, 0, 0, 1});
    sys.push_back(Body{1, 0, 0, 0, 1, 0, 1e-8});

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    double h = 1e-3;
    for (double i = 0; i < 3.141592653589793; i += h) {
        findAcceleration(sys, h);
        std::cout << "i = " << i << "\n";
        for (int i = 0; i < 2; ++i) {
            
            sys[i].printOut();
        }
    }

    for (int i = 0; i < 2; ++i) {
        sys[i].printOut();
    }    
}

int main(void) {
    testGroup2();
}