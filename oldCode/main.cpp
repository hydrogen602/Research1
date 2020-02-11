#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include "body.h"
#include "kDeltaVector.h"

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
        vect3 dv = {accVector.x * h, accVector.y * h, accVector.z * h}; //system[i].getIntegratedVelocity(accVector, h);
        // k1 = h * F(...)
        vect3 x = system[i].getIntegratedPosition(dv, h);
        k.push_back(kDelta(x.x, x.y, x.z, accVector.x * h, accVector.y * h, accVector.z * h));
    }

    return k;
}

std::vector<Body> newAdvanceState(const std::vector<Body> &sys, const std::vector<kDelta> &k, double kFactor) {
    std::vector<Body> state(sys); // state is yn

    // modifies state using k
    if (state.size() != k.size()) {
        throw ERR_VECTOR_SIZE_MISMATCH;
    }

    for (int i = 0; i < state.size(); ++i) {
        state[i].integrate(k[i], kFactor);
    }

    return state;
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
     * idk what to do with x for now
     */

    // assemble yn
    // position and velocity rn

    // k1 = h * F(xn, yn)
    std::vector<kDelta> k1 = getKDelta(system, h);

    std::cout << "k1: ";
    for (int i = 0; i < k1.size(); i++)
    {
        k1[i].printOut();
    }
    

    std::vector<Body> shiftedState = newAdvanceState(system, k1, 1.0/2);

    // k2 = h * F(xn + h/2, yn + k1/2)
    std::vector<kDelta> k2 = getKDelta(shiftedState, h);

    std::cout << "k2: ";
    for (int i = 0; i < k2.size(); i++)
    {
        k2[i].printOut();
    }

    shiftedState = newAdvanceState(system, k2, 1.0/2);

    // k3 = hF(xn + h/2, yn + k2/2)
    std::vector<kDelta> k3 = getKDelta(shiftedState, h);

    std::cout << "k3: ";
    for (int i = 0; i < k3.size(); i++)
    {
        k3[i].printOut();
    }

    shiftedState = newAdvanceState(system, k3, 1);

    // k4 = hF(xn + h, yn + k3)
    std::vector<kDelta> k4 = getKDelta(shiftedState, h);

    std::cout << "k4: ";
    for (int i = 0; i < k4.size(); i++)
    {
        k4[i].printOut();
    }

    // y_n+1 = y_n + 1/6 * (k1 + 2k2 + 3k3 + k4)

    std::vector<kDelta> K;
    if (k1.size() != k2.size() || k2.size() != k3.size() || k3.size() != k4.size()) {
        throw ERR_VECTOR_SIZE_MISMATCH;
    }

    for (int i = 0; i < k1.size(); ++i) {
        kDelta tmp = k1[i];
        tmp += k2[i] * 2;
        tmp += k3[i] * 2;
        tmp += k4[i];
        std::cout << "combined k: ";
        tmp.printOut();
        K.push_back(tmp);
    }

    for (int i = 0; i < K.size(); ++i) {
        kDelta tmp = K[i] * (1.0/6);
        tmp.printOut();
    }

    advanceState(system, K, 1.0/6);

}

/* ======================================================================
 *                            TEST CODE
 * ======================================================================
 */

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
        #if DEBUG
            std::cout << "i = " << i << "\n";
        #endif
        for (int i = 0; i < 2; ++i) {
            #if DEBUG
                sys[i].printOut();
            #endif
        }
    }

    for (int i = 0; i < 2; ++i) {
        sys[i].printOut();
    }    
}

void testGroup3_RK4() {
    std::vector<Body> sys;

    sys.push_back(Body{0, 0, 0, 0, 0, 0, 1});
    sys.push_back(Body{1, 0, 0, 0, 1, 0, 1e-8});

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    double h = 1e-3;
    for (double i = 0; i < 3.141592653589793; i += h) {
        #if DEBUG
            std::cout << "i = " << i << "\n";
        #endif
        rk4(sys, h);
        for (int i = 0; i < 2; ++i) {
            #if DEBUG
                sys[i].printOut();
            #endif
        }
    }

    std::cout << "Final Result:\n";
    for (int i = 0; i < 2; ++i) {
        sys[i].printOut();
    }
}

int main(void) {
    std::cerr << "Starting...\n";
    testGroup3_RK4();
    std::cerr << "Done\n";
}