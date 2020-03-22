#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
#include "state.h"

#define square(x) ((x) * (x))

const double PI = 3.141592653589793;

const int orbits = 1;//00;

State::State(double hVal): h{hVal} {}

void State::addBody(double x, double y, double z, double vx, double vy, double vz, double m) {
  data.addBody(x, y, z, vx, vy, vz);

  masses.push_back(m);

  if (masses.size() * 6 != data.size()) {
    throw ERR_VECTOR_SIZE_MISMATCH;
  }
}

int State::size() const {
  return masses.size();
}

void State::printOut() const {
  std::cout << "[\n";
  for (int i = 0; i < data.size(); i += 6) {
    printf("  ");
    data.printOut(i);
  }
  std::cout << "]\n";
}

double State::computeKineticEnergy() const {
    //  1/2 m v^2
    double energy = 0;
    
    for (int i = 0; i < data.size(); i += 6) {
        // v^2 = vx^2 + vy^2 + vz^2

        double vSq = square(data[i + 3]) + square(data[i + 4]) + square(data[i + 5]);
        energy += 0.5 * masses[i / 6] * vSq;
        //printf("KE[%d] = %e\n", i / 6, 0.5 * masses[i / 6] * vSq);
    }

    return energy;
}

double State::computePotentialEnergy() const {
    // -G (mM) / R
    double energy;

    for (int i = 0; i < data.size(); i += 6)
    {
        for (int j = i + 6; j < data.size(); j += 6)
        {
            // compute R
            double dSq = square(data[i] - data[j]) + square(data[i+1] - data[j+1]) + square(data[i+2] - data[j+2]);
            double r = sqrt(dSq);

            // G is 1
            energy += - (masses[i / 6] * masses[j / 6] / r);

            //printf("PE[%d] on [%d] = %e\n", i / 6, j / 6, - (masses[i / 6] * masses[j / 6] / r));
        }
        
    }
    return energy;
}

double State::computeEnergy() const {
    return computeKineticEnergy() + computePotentialEnergy();
}

void State::derivative(Vector& d) const {
    if (d.size() != data.size()) {
        d.resize(data.size(), 0);
    }

    /*  [ x  ]      [ vx ]
     *  [ y  ]      [ vy ]
     *  [ z  ]  ==> [ vz ]
     *  [ vx ]  ==> [ ax ]
     *  [ vy ]      [ ay ]
     *  [ vz ]      [ az ]
     */

    for (int i = 0; i < data.size(); i += 6) {
        d[i + 0] = data[i + 3];
        d[i + 1] = data[i + 4];
        d[i + 2] = data[i + 5];
        // find acceleration

        vect3 accVector = {0, 0, 0};

        for (int j = 0; j < data.size(); j += 6) {
            if (i != j) {
                double dSq = square(data[i] - data[j]) + square(data[i+1] - data[j+1]) + square(data[i+2] - data[j+2]);
                // a = g * m / r^2
                // g = 1
                // m = in solar masses

                double accScalar = masses[j / 6] / dSq; // magnitude of a

                // vect3 dirUnitVec = system[i].unitVectTo(system[j]); // dir of a

                double d = sqrt(dSq); // length of vector

                vect3 c;
                c.x = data[j] - data[i];
                c.y = data[j+1] - data[i+1];
                c.z = data[j+2] - data[i+2];
                // now c is a vector pointing to b from this
                c.x /= d;
                c.y /= d;
                c.z /= d;

                // c is now a unit vector pointing to object j

                c.x *= accScalar;
                c.y *= accScalar;
                c.z *= accScalar;

                accVector.x += c.x;
                accVector.y += c.y;
                accVector.z += c.z; // i and j forces get calculated twice
            }
        }

        // accVector is acceleration

        d[i + 3] = accVector.x;
        d[i + 4] = accVector.y;
        d[i + 5] = accVector.z;
    }
}

void State::euler1() {
    // y_n+1 = y_n + k
    // k = h * F(x, y)

    Vector k;
    derivative(k);
    k *= h;

    // advance
    (*this) += k;
}

void State::kickStep1() {
    // first integrate acc to vel, then vel to position
    
    Vector k;
    derivative(k);
    
    // kick
    for (int i = 0; i < data.size(); i += 6) {
        k[i + 0] += k[i + 3] * h;
        k[i + 1] += k[i + 4] * h;
        k[i + 2] += k[i + 5] * h;
    }

    // step
    k *= h;
    (*this) += k;
}

void State::rk4() {
    /*
     * Runge-Kutta
     * 
     * y' = F(x, y)
     * 
     * y_n+1 = y_n + 1/6 * (k1 + 2k2 + 2k3 + k4) + O(h^5)
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

    Vector oldState(data);

    // k1 = hF(xn, yn)
    Vector k1;
    derivative(k1);
    k1 *= h;

    // k2 = hF(xn + h/2, yn + k1/2)
    (*this) += k1 / 2;

    Vector k2;
    derivative(k2);
    k2 *= h;

    data = oldState;
    // k3 = hF(xn + h/2, yn + k2/2)
    
    (*this) += k2 / 2;

    Vector k3;
    derivative(k3);
    k3 *= h;

    data = oldState;
    // k4 = hF(xn + h, yn + k3)

    (*this) += k3;

    Vector k4;
    derivative(k4);
    k4 *= h;

    data = oldState;
    // 1/6 * (k1 + 2k2 + 2k3 + k4)

    Vector K(data.size());

    K += k1;

    k2 *= 2;
    K += k2;

    k3 *= 2;
    K += k3;

    K += k4;

    K *= 1.0/6;

    (*this) += K;

}

State State::operator+=(Vector delta) {
    if (data.size() != delta.size()) {
        throw ERR_VECTOR_SIZE_MISMATCH;
    }

    for (int i = 0; i < data.size(); ++i) {
        data[i] += delta[i];
    }

    return *this;
}

void testGroup0() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8);

    sys.printOut();
}

void testGroup1_Euler1() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8);

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

    sys.addBody(0, 0, 0, 0, 0, 0, 1);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8);

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

    sys.addBody(0, 0, 0, 0, 0, 0, 1);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8);

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

void testGroup4_Energy() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    for (double i = 0; i < orbits * PI * 2; i += h) { // orbits * 2 * PI

        sys.kickStep1();

        //printf("t = %.3f; E = %e\n", i, sys.computeEnergy());

        printf("%.3f\t%e\n", i, sys.computeEnergy());
    }

    //std::cout << "Final Result:\n";
    //sys.printOut();
}

int main() {
    std::cerr << "Starting...\n";

    //try
    //{
        testGroup4_Energy();
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
