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

std::vector<kDelta> getKDelta(std::vector<Body> &system, double h) {
    std::vector<kDelta> k;

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

        //system[i].integrate(accVector, h);
        vect3 v = system[i].getIntegratedVelocity(accVector, h);
        // k1 = h * F(...)
        k.push_back(kDelta{v.x * h, v.y * h, v.z * h, accVector.x * h, accVector.y * h, accVector.z * h});
    }

    return k;
}

void advanceState(std::vector<Body> &state, const std::vector<kDelta> &k, double kFactor) {
    // modifies state using k
    if (state.size() != k.size()) {
        throw ERR_VECTOR_SIZE_MISMATCH;
    }

    for (int i = 0; i < state.size(); ++i) {
        state[i].integrate(k[i], kFactor);
    }
}

void rk4(std::vector<Body> &system, double h) {
    /*
     * Runge-Kutta
     * 
     * y' = F(x, y)
     * 
     * y_n+1 = y_n + 1/6 * (k1 + 2k2 + 3k3 + k4) + O(h^5)
     * 
     * k1 = hF(xn, yn)
     * k2 = hF(xn + h/2, yn + k1/2)
     * k3 = hF(xn + h/2, yn + k2/2)
     * k4 = hF(xn + h, yn + k3)
     * 
     * y is position & velocity
     * y' is velocity & acceleration
     * 
     * 
     */

    // assemble yn
    // position and velocity rn

    std::vector<Body> state; // state is yn
    for (int i = 0; i < system.size(); ++i) {
        state.push_back(system[i]);
    }
    // state has copies of system

    // k1 = h * F(xn, yn)
    std::vector<kDelta> k1 = getKDelta(system, h);

    advanceState(state, k1, 1/2);

    // k2 = h * F(xn + h/2, yn + k1/2)
    std::vector<kDelta> k2 = getKDelta(state, h);
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
    std::vector<Body> sys;

    sys.push_back(Body{0, 0, 0, 0, 0, 0, 1});
    sys.push_back(Body{1, 0, 0, 0, 1, 0, 1e-8});
    //testGroup2();
    rk4(sys, 1e-3);
}